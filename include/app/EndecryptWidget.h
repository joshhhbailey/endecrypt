#ifndef EndecryptWidget_H_
#define EndecryptWidget_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>

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
    QString readFile();
    void writeFile(std::string _contents, bool _ende);  // _ende: true = encrypt, false = decrypt

    QLineEdit* m_fileLE;
    QString m_filePath;
    QLabel* m_logLabel;

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
        QString user = std::getenv("USER");
        QString m_prefix = "/Users/" + user + "/";
    #endif
    
};

#endif  // _EndecryptWidget_H_