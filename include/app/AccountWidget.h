#ifndef ACCOUNTWIDGET_H_
#define ACCOUNTWIDGET_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>

#include <cryptopp/rsa.h>

#include <string>

class AccountWidget : public QGroupBox
{
    Q_OBJECT
public:
    AccountWidget();

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
};

#endif  // _ACCOUNTWIDGET_H_