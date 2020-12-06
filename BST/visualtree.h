#ifndef VISUALTREE_H
#define VISUALTREE_H

#include <QMainWindow>
#include <tree.h>
#include <QPaintEvent>

namespace Ui {
class VisualTree;
}

class VisualTree : public QMainWindow
{
    Q_OBJECT

public:
    explicit VisualTree(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent *event);
    ~VisualTree();

private slots:
    void on_insert_button_clicked();

    void on_Root_set_clicked();

   // void on_delete_button_clicked();



private:
    bool DrawTree{false};
    Tree::Node* _node;
    Ui::VisualTree *ui;
};
#endif // VISUALTREE_H
