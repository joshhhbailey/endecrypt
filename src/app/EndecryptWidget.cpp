#include <QtWidgets/QGridLayout>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <cryptopp/default.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

#include "EndecryptWidget.h"

EndecryptWidget::EndecryptWidget()
{
    createWidgets();
    createLayouts();
    createConnections();
}

void EndecryptWidget::createWidgets()
{
    m_fileLE = new QLineEdit();
    m_keyLE = new QLineEdit();
    m_keyLE->setEchoMode(QLineEdit::Password);

    m_fileLabel = new QLabel(tr("File:"));
    m_keyLabel = new QLabel(tr("Endecrypt key:"));
    m_logLabel = new QLabel(tr("Welcome!"));
    
    m_encryptButton = new QPushButton(tr("Encrypt"));
    m_decryptButton = new QPushButton(tr("Decrypt"));
    m_browseButton = new QPushButton(tr("Browse"));
}

void EndecryptWidget::createLayouts()
{
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(m_fileLabel, 0, 0, 1, 1);
    mainLayout->addWidget(m_fileLE, 0, 1, 1, 1);
    mainLayout->addWidget(m_browseButton, 0, 2, 1, 1);
    mainLayout->addWidget(m_keyLabel, 1, 0, 1, 1);
    mainLayout->addWidget(m_keyLE, 1, 1, 1, 1);
    mainLayout->addWidget(m_encryptButton, 1, 2, 1, 1);
    mainLayout->addWidget(m_decryptButton, 1, 3, 1, 1);
    mainLayout->addWidget(m_logLabel, 2, 0, 1, 4);
    setLayout(mainLayout);
}

void EndecryptWidget::createConnections()
{
    connect(m_keyLE, SIGNAL(textChanged(const QString &)), this, SLOT(keyChanged(const QString &)));
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    connect(m_encryptButton, SIGNAL(clicked()), this, SLOT(encryptButtonClicked()));
    connect(m_decryptButton, SIGNAL(clicked()), this, SLOT(decryptButtonClicked()));
}

QString EndecryptWidget::readFile()
{
    QString contents = "";

    // Check file exists
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return contents;
    }

    // Extract file contents
    QTextStream in(&file);
    while(!in.atEnd())
    {
        contents += in.readLine();
    }
    return contents;
}

void EndecryptWidget::writeFile(std::string _contents, bool _ende)
{
    // Encrypted or decrypted
    QString postfix;
    if (_ende)
    {
        postfix = ".en";
    }
    else
    {
        postfix = ".de";
    }

    // Create file
    QFile file(m_prefix + "out" + postfix);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    // Write
    QTextStream out(&file);
    out << _contents.c_str();
}

void EndecryptWidget::keyChanged(const QString &)
{
    m_key = m_keyLE->text();
}

void EndecryptWidget::encryptButtonClicked()
{
    m_plainText = readFile().toStdString();

    if (m_plainText == "")
    {
        m_logLabel->setText(tr("File is empty... Nothing to encrypt."));
        return;
    }

    // Encrypt (MAC - https://www.cryptopp.com/wiki/DefaultEncryptorWithMAC)
    CryptoPP::StringSource ss1(m_plainText, true,
    new CryptoPP::DefaultEncryptorWithMAC(
        (CryptoPP::byte*)&m_key.toStdString()[0], m_key.toStdString().size(),
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(m_encryptedText)
            )
        )
    );

    writeFile(m_encryptedText, true);
    m_logLabel->setText(tr("Encryption complete."));
}

void EndecryptWidget::decryptButtonClicked()
{
    m_encryptedText = readFile().toStdString();

    if (m_encryptedText == "")
    {
        m_logLabel->setText(tr("File is empty... Nothing to decrypt."));
        return;
    }

    // Decrypt (MAC - https://www.cryptopp.com/wiki/DefaultEncryptorWithMAC)
    CryptoPP::StringSource ss2(m_encryptedText, true,
    new CryptoPP::HexDecoder(
        new CryptoPP::DefaultDecryptorWithMAC(
            (CryptoPP::byte*)&m_key.toStdString()[0], m_key.toStdString().size(),
                new CryptoPP::StringSink(m_decryptedText)
            )
        )
    );

    writeFile(m_decryptedText, false);
    m_logLabel->setText(tr("Decryption complete."));
}

void EndecryptWidget::browseButtonClicked()
{
    m_filePath = QFileDialog::getOpenFileName(this);
    m_fileLE->setText(m_filePath);
}
