#include <QtWidgets/QGridLayout>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

#include <cryptopp/files.h>
#include <cryptopp/osrng.h>

#include "AccountWidget.h"

AccountWidget::AccountWidget()
{
    createWidgets();
    createLayouts();
    createConnections();

    loadKeys();
}

void AccountWidget::createWidgets()
{
    m_fileLE = new QLineEdit();

    m_encryptButton = new QPushButton(tr("Encrypt"));
    m_decryptButton = new QPushButton(tr("Decrypt"));
    m_browseButton = new QPushButton(tr("Browse"));
    m_generateButton = new QPushButton(tr("Generate Keys"));
}

void AccountWidget::createLayouts()
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
    setLayout(mainLayout);
}

void AccountWidget::createConnections()
{
    connect(m_browseButton, SIGNAL(clicked()), this, SLOT(browseButtonClicked()));
    connect(m_generateButton, SIGNAL(clicked()), this, SLOT(generateButtonClicked()));
}

void AccountWidget::loadKeys()
{
    if (QFile::exists("rsaPrivate.key"))
    {
        CryptoPP::FileSource inputPrivate("rsaPrivate.key", true);
        m_rsaPrivate.BERDecode(inputPrivate);
    }

    if (QFile::exists("rsaPublic.key"))
    {
        CryptoPP::FileSource inputPublic("rsaPublic.key", true);
        m_rsaPublic.BERDecode(inputPublic);
    }
}

void AccountWidget::encryptButtonClicked()
{
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Encryptor e(m_rsaPublic);

    CryptoPP::StringSource(m_plain, true,
        new CryptoPP::PK_EncryptorFilter(rng, e,
            new CryptoPP::StringSink(m_encrypted)
        ) // PK_EncryptorFilter
    ); // StringSource
}

void AccountWidget::decryptButtonClicked()
{
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::RSAES_OAEP_SHA_Decryptor d(m_rsaPrivate);

    CryptoPP::StringSource(m_encrypted, true,
        new CryptoPP::PK_DecryptorFilter(rng, d,
            new CryptoPP::StringSink(m_decrypted)
        ) // PK_DecryptorFilter
    ); // StringSource
}

void AccountWidget::browseButtonClicked()
{
    m_file = QFileDialog::getOpenFileName(this);
    m_fileLE->setText(m_file);
}

void AccountWidget::generateButtonClicked()
{
    // Generate
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 2048);

    m_rsaPrivate = CryptoPP::RSA::PrivateKey(params);
    m_rsaPublic = CryptoPP::RSA::PublicKey(params);

    // Save keys
    CryptoPP::FileSink outputPrivate("rsaPrivate.key");
    m_rsaPrivate.DEREncode(outputPrivate);

    CryptoPP::FileSink outputPublic("rsaPublic.key");
    m_rsaPublic.DEREncode(outputPublic);
}
