#include "tree.h"
#include <iostream>
#include <vector>
#include <QPoint>

namespace Tree {

    Node::Node(Data NewData) {
        _data = NewData;
    }

    Node::~Node() {
        delete _left;
        delete _right;
    }

    void Node::Insert(Data NewData) {
        if (NewData.val < _data.val)
        {
            if (_left == nullptr){
                left_nodes++;
                _left = new Node(NewData);
                _left->_data.new_node = true;
            }
            else{
                _left->Insert(NewData); //first goes to left side and again calls the Insert()function
            }

        }
        else if (NewData.val > _data.val)
        {
            if (_right == nullptr){
                right_nodes++;
                _right = new Node(NewData);
                _right->_data.new_node = true;
            }
            else{
                _right->Insert(NewData);//first goes to right side and again calls the Insert() function
            }
        }
    }

    void Node::deleteItem(Data data){


    }

    void Node::ResetLastLabel(){
        if (_left != nullptr){
            _left->_data.new_node = false;
            _left->ResetLastLabel();
        }

        if (_right != nullptr){
            _right->_data.new_node = false;
            _right->ResetLastLabel();
        }
    }

    bool Node::Contain(int number) {

        //searching new number in the left side of the tree
        if (number < _data.val) {
            if (_left == nullptr){
                return false;
            }
            else {
                _left->Contain(number);
            }
        }

        //searching new number in the right side of the tree
        else if (number > _data.val)
        {
            if (_right == nullptr) {
                return false;
            }
            else {
                _right->Contain(number);
            }
        }

        //can't find anywhere and return true
        else {
            return true;
        }
    }

    void Node::GetSortedVector(std::vector<int>& a)
    {
        if (_left != nullptr){
            _left->GetSortedVector(a);
        }

        //arranging data in sorted form first collects all the left datas and then
        //collects right datas
        a.push_back(_data.val);


        if (_right != nullptr){
            _right->GetSortedVector(a);
        }
    }

    std::vector<Data> Node::SetPositionOfNodesForVisualization(){
        int level{0},pos{1};
        this->SetLevel(level);
        this->SetPos(pos);
        this->SetDataForDrawing(*this);
        std::vector<Data> vec;
        this->ReturnDataVector(vec);

        return vec;

    }

//a vector returning function to draw edes between nodes
    std::vector<QPoint> Node::GetVectorOfLinesBetwenNodes(){
        std::vector<QPoint> vec;
        this->LoopForLinesConnection(vec);
        return vec;
    }

//function that collects the nodes location to connect nodes using edge
    void Node::LoopForLinesConnection(std::vector<QPoint>& vec){

        //getting all the position of left_child + DrawSize/2
        if(_left != nullptr){
            QPoint point(_data.posX,_data.posY);
            vec.push_back(point);
            _left->LoopForLinesConnection(vec);
        }

        //getting all the position of right_child + DrawSize/2
        if(_right != nullptr){
            QPoint point(_data.posX,_data.posY);
            vec.push_back(point);
            _right->LoopForLinesConnection(vec);
        }

        //for root node + DrawSize/2
        QPoint point(_data.posX,_data.posY);
        vec.push_back(point);
    }

    void Node::ReturnDataVector(std::vector<Data>& vector){

        //collecting left node data
        if(_left != nullptr){
            _left->ReturnDataVector(vector);
        }

        vector.push_back(_data);

        //collecting right node data
        if(_right != nullptr){
            _right->ReturnDataVector(vector);
        }
    }


    void Node::SetDataForDrawing(Node& root){
        //go to left and analyse where to go right or left
        if(_left != nullptr){
            _left->SetDataForDrawing(root);
        }

        _data.posY = (_data.level* root.DrawingSize)+root.start_pos.y();  //0*34+150

        //Shifting nodes to the left of it's parent
        if(_data.pos < root._data.pos){
            _data.posX = root.start_pos.x() - ((root._data.pos - _data.pos)*root.DrawingSize);
        }

        //Shifting nodes to the right of it's parent
        else if(_data.pos > root._data.pos){
            _data.posX = root.start_pos.x() + ((_data.pos - root._data.pos)*root.DrawingSize);
        }
        //if it itself a root
        else{
            _data.posX = root.start_pos.x();
        }

        //go to right and analyse again where to go right or left
        if(_right != nullptr){
            _right->SetDataForDrawing(root);
        }
    }


    //in binary tree we make the position from left to right so right's node has higher position by 1
    void Node::SetPos(int &pos){
        if(_left != nullptr){
            _left->SetPos(pos);
        }
        _data.pos = pos;
        //incrementing position by 1
        pos++;
        if(_right != nullptr){
            _right->SetPos(pos);
        }
    }

    void Node::SetLevel(int& level){
        _data.level = level;
        level++;
        if(_left != nullptr){
            _left->SetLevel(level);
        }
        if(_right != nullptr){
            _right->SetLevel(level);
        }
        //if both left and right nodes are already there then initially increased level decreases
        level--;
    }
}
