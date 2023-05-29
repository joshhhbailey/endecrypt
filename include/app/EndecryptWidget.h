#ifndef EndecryptWidget_H_
#define EndecryptWidget_H_

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLabel>

#include <string>

class EndecryptWidget : public QGroupBox
{
    Q_OBJECT
public:
    EndecryptWidget();

public slots:
    void keyChanged(const QString &);
    void encryptButtonClicked();
    void decryptButtonClicked();
    void browseButtonClicked();

private:
    void createWidgets();
    void createLayouts();
    void createConnections();
    
    QString readFile();
    void writeFile(std::string _contents, bool _ende);  // _ende: true = encrypt, false = decrypt

    // Line edits
    QLineEdit* m_fileLE;
    QLineEdit* m_keyLE;

    // Labels
    QLabel* m_fileLabel;
    QLabel* m_keyLabel;
    QLabel* m_logLabel;

    // Buttons
    QWidget* m_buttonsWidget;
    QPushButton* m_encryptButton;
    QPushButton* m_decryptButton;
    QPushButton* m_browseButton;

    QString m_filePath;
    QString m_key;
    
    std::string m_plainText;
    std::string m_encryptedText;
    std::string m_decryptedText;

    #ifdef _WIN32
        QString m_user = std::getenv("USERNAME");
        QString m_prefix = "C:/Users/" + m_user + "/";
    #elif __APPLE__
        QString m_user = std::getenv("USER");
        QString m_prefix = "/Users/" + m_user + "/";
    #endif
};

#endif  // _EndecryptWidget_H_