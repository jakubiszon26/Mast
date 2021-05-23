#ifndef APT_PREFERENCES_H
#define APT_PREFERENCES_H

#include <QWidget>
#include <QListWidgetItem>

static QString selectedRepo;
static QString selectedFile;


namespace Ui {
class Apt_Preferences;
}

class Apt_Preferences : public QWidget
{
    Q_OBJECT

public:
    explicit Apt_Preferences(QWidget *parent = nullptr);
    ~Apt_Preferences();
private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_on_and_off_button_clicked();
    void on_repositories_in_file_list_itemClicked(QListWidgetItem *item);
    void write_to_file();
    void refresh_repositories_list();
    void on_ppa_submit_button_clicked();
    void on_select_deb_button_clicked();
    void on_install_button_clicked();
    void ReadOut();
    void ReadErr();
    void HandleFinished();
    void command(QString command, QStringList args, QString finishMessage, bool isMessageBox);

    private:
        Ui::Apt_Preferences *ui;
};

#endif // APT_PREFERENCES_H
