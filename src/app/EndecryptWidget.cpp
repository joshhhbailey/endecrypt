#include <QtWidgets/QGridLayout>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

#include "EndecryptWidget.h"

EndecryptWidget::EndecryptWidget()
{
    createWidgets();
    createLayouts();
    createConnections();
    loadKeys();
}

void EndecryptWidget::createWidgets()
{
    m_fileLE = new QLineEdit();
    m_logLabel = new QLabel("Welcome!");

    m_encryptButton = new QPushButton(tr("Encrypt"));
    m_decryptButton = new QPushButton(tr("Decrypt"));
    m_browseButton = new QPushButton(tr("Browse"));
    m_generateButton = new QPushButton(tr("Generate Keys"));
}

void EndecryptWidget::createLayouts()
{
    QGridLayout* mainLayout = new QGridLayout();
    mainLayout->addWidget(m_fileLE, 0, 0, 1, 1);
    mainLayout->addWidget(m_browseButton, 0, 1, 1, 1);

    m_buttonsWidget = new QWidget();
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(m_generateButton);
    buttonsLayout->addWidget(m_encryptButton);
    buttonsLayout->addWidget(m_decryptButton);

    m_buttonsWidget->setLayout(buttonsLayout);
    mainLayout->addWidget(m_buttonsWidget, 1, 0, 1, 2);
    mainLayout->addWidget(m_logLabel, 2, 0, 1, 2);
    setLayout(mainLayout);
}

void EndecryptWidget::createConnections()
{
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    connect(m_generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
    connect(m_encryptButton, SIGNAL(clicked()), this, SLOT(encryptButtonClicked()));
    connect(m_decryptButton, SIGNAL(clicked()), this, SLOT(decryptButtonClicked()));
}

void EndecryptWidget::loadKeys()
{
    if (QFile::exists(m_prefix + "rsaPrivate.key"))
    {
        CryptoPP::FileSource inputPrivate((m_prefix.toStdString() + "rsaPrivate.key").c_str(), true);
        m_rsaPrivate.BERDecode(inputPrivate);
    }

    if (QFile::exists(m_prefix + "rsaPublic.key"))
    {
        CryptoPP::FileSource inputPublic((m_prefix.toStdString() + "rsaPublic.key").c_str(), true);
        m_rsaPublic.BERDecode(inputPublic);
    }
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

void EndecryptWidget::encryptButtonClicked()
{
    m_plain = readFile().toStdString();

    // Encrypt
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(m_rsaPublic);

    CryptoPP::StringSource ss1(m_plain, true,
        new CryptoPP::PK_EncryptorFilter(rng, e,
            new CryptoPP::StringSink(m_encrypted)
        ) // PK_EncryptorFilter
    ); // StringSource

    writeFile(m_encrypted, true);

    m_logLabel->setText("Encryption complete.");
}

void EndecryptWidget::decryptButtonClicked()
{
    m_encrypted = readFile().toStdString();
    //QString s = QString::fromStdString(m_encrypted);
    //m_logLabel->setText(s);

    // Decrypt
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(m_rsaPrivate);

    CryptoPP::StringSource ss2(m_encrypted, true,
        new CryptoPP::PK_DecryptorFilter(rng, d,
            new CryptoPP::StringSink(m_decrypted)
        ) // PK_DecryptorFilter
    ); // StringSource

    writeFile(m_decrypted, false);

    m_logLabel->setText("Decryption complete.");
}

void EndecryptWidget::browseButtonClicked()
{
    m_filePath = QFileDialog::getOpenFileName(this);
    m_fileLE->setText(m_filePath);
}

void EndecryptWidget::generateButtonClicked()
{
    // Generate
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);

    m_rsaPrivate = CryptoPP::RSA::PrivateKey(params);
    m_rsaPublic = CryptoPP::RSA::PublicKey(params);

    // Save keys
    CryptoPP::FileSink outputPrivate((m_prefix.toStdString() + "rsaPrivate.key").c_str());
    m_rsaPrivate.DEREncode(outputPrivate);

    CryptoPP::FileSink outputPublic((m_prefix.toStdString() + "rsaPublic.key").c_str());
    m_rsaPublic.DEREncode(outputPublic);

    m_logLabel->setText("Key generation complete.");
}
