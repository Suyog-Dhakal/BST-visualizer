#pragma once
#include <vector>
#include <QPoint>

namespace Tree {
    struct Data {
        int val;
        int level;
        int pos;
        int posX{0};
        int posY{0};
        bool new_node{false};
    };

    class Node
    {

    private:
        Node *_left = nullptr, *_right = nullptr;

        void ReturnDataVector(std::vector<Data>& vector);
        void LoopForLinesConnection(std::vector<QPoint>& vec);
        void SetDataForDrawing(Node& root);
        void SetPos(int& pos);
        void SetLevel(int& level);

    public:
        const int DrawingSize{34};   //circle diameter(size)
        const QPoint start_pos{360,80};   //paint_node starts working from this point
        static int left_nodes;
        static int right_nodes;
        Data _data;
        Node(Data NewData);
        ~Node();
        bool Contain(int number);
        void GetSortedVector(std::vector<int>& a);
        void Insert(Data NewData);
        void deleteItem(Data data);
        void ResetLastLabel(); //for coloring the recently inserted node

        std::vector<Data> SetPositionOfNodesForVisualization();
        std::vector<QPoint> GetVectorOfLinesBetwenNodes();

    };
}
