#ifndef EndecryptWidget_H_
#define EndecryptWidget_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>

#include <cryptopp/rsa.h>

#include <string>

class EndecryptWidget : public QGroupBox
{
    Q_OBJECT
public:
    EndecryptWidget();

public slots:
    void encryptButtonClicked();
    void decryptButtonClicked();
    void browseButtonClicked();
    void generateButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    
    void loadKeys();

    QLineEdit* m_fileLE;
    QString m_file;

    // Buttons
    QWidget* m_buttonsWidget;
    QPushButton* m_encryptButton;
    QPushButton* m_decryptButton;
    QPushButton* m_browseButton;
    QPushButton* m_generateButton;

    // Keys
    CryptoPP::RSA::PrivateKey m_rsaPrivate;
    CryptoPP::RSA::PublicKey m_rsaPublic;

    std::string m_plain;
    std::string m_encrypted;
    std::string m_decrypted;

    #ifdef _WIN32
        QString m_prefix = "";
    #elif __APPLE__
        QString m_prefix = "/Users/$USER/";
    #endif
    
};

#endif  // _EndecryptWidget_H_