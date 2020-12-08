#include "visualtree.h"
#include "ui_visualtree.h"
#include <iostream>
#include <QString>
#include "tree.h"
#include <QPainter>
#include <QPoint>
#include <string>


//initializing the variables of class Node of namespace Tree
int Tree::Node::left_nodes = 0;
int Tree::Node::right_nodes = 0;


//here all of the functions are the children of QWidget *parent so this parent controll whole app
VisualTree::VisualTree(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VisualTree)
    {
        ui->setupUi(this);          //showing ui in the window
    }

VisualTree::~VisualTree()
{
    delete _node;
    delete ui;
}


void VisualTree::on_insert_button_clicked()
{
    QString raw_data = ui->Input_text->text();
    ui->Input_text->setText("");

    Tree::Data _data;
            _data.val = raw_data.toInt();
            if(!(_node->Contain(raw_data.toInt()))){
                _node->ResetLastLabel();
                _node->Insert(_data);


            }

    DrawTree = true;
    update();
}


void VisualTree::on_Root_set_clicked()
{
    int root = ui->Root_inp->text().toInt();

    Tree::Data r_data;
    r_data.val = root;

    _node = new Tree::Node(r_data);

    //handling signals after clicking the button (making root input line edit
    // root button inactive after setting root)
    ui->Root_inp->setEnabled(false);
    ui->Root_set->setEnabled(false);
}
void VisualTree::on_delete_button_clicked()
{
    int data;
    if(!(_node->Contain(data))){
       // _node->ResetLastLabel();
       // _node->deleteItem(data);


    }
}


void VisualTree::paintEvent(QPaintEvent *event){

    //making pen ready to draw edges and nodes, here paint_node draws nodes and edges
    if(DrawTree == true){
        QPainter paint_node(this);
        paint_node.setPen(QPen(Qt::blue,2));
        std::vector<Tree::Data> nodes_data = _node->SetPositionOfNodesForVisualization();

        //to connect two nodes from their centre part size variable is created
        const int size = _node->DrawingSize/2;
        QPoint line_pos;
        line_pos.setX(_node->start_pos.x()+size);
        line_pos.setY(_node->start_pos.y()+size);


        //getting the coordinates to drawline (edge) from tree.cpp file
        std::vector<QPoint> nodes_lines = _node->GetVectorOfLinesBetwenNodes();
        for(const auto& a : nodes_lines){


            //drawing edges using (x1,y1) and (x2, y2)
            //this line prints first edge form root to it's either left or right child
            paint_node.drawLine(line_pos.x(),line_pos.y(),a.x()+size,a.y()+size);

            //updating coordinate for line_pos to draw another edge
            line_pos.setX(a.x()+size);
            line_pos.setY(a.y()+size);
        }

        //making brush cyan
        paint_node.setBrush(QBrush(QColor(Qt::cyan)));

        //drawing circles(drawEllipse making a and b equal to make circle) for nodes and brushing with paint_node
        for(const auto& a : nodes_data){
            QPoint node_pos(a.posX,a.posY);

            //for old nodes
            if(a.new_node == false){
                paint_node.drawEllipse(a.posX,a.posY,_node->DrawingSize,_node->DrawingSize);
            }
            //for new nodes
            else{

                //setting up brush of paint_node for new node and drawing red node
                paint_node.setBrush(QBrush(QColor(Qt::red)));
                paint_node.drawEllipse(a.posX,a.posY,_node->DrawingSize,_node->DrawingSize);

                //making brush to it's original color
                paint_node.setBrush(QBrush(QColor(Qt::cyan)));
            }

            //for drawing node value
            paint_node.drawText(QRectF(QPointF(node_pos),QSizeF(QSize(34,31))),QString::number(a.val),QTextOption(Qt::AlignCenter));
        }
    }
}
