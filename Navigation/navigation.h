#ifndef NAVIGATION_H
#define NAVIGATION_H

// http://qt-project.org/quarterly/view/location_and_mapping_services
// http://stackoverflow.com/questions/8515598/how-to-add-google-maps-in-my-application-in-qt

#include <QWidget>

namespace Ui {
class Navigation;
}

class Navigation : public QWidget
{
    Q_OBJECT
    
public:
    explicit Navigation(QWidget *parent = 0);
    ~Navigation();
    
private:
    Ui::Navigation *ui;
};

#endif // NAVIGATION_H
