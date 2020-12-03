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
    public:
        const int DrawingSize{34};  //circle radius
        const QPoint start_pos{360,80};  //initial position of root node

        static int left_nodes;
        static int right_nodes;
        Data _data;

        bool Contain(int number);
        void GetSortedVector(std::vector<int>& a);
        void Insert(Data NewData);
        void ResetLastLabel();

        std::vector<Data> SetPositionOfNodesForVisualization();
        std::vector<QPoint> GetVectorOfLinesBetwenNodes();

        Node(Data NewData);
        ~Node();

    private:
        Node *_left = nullptr, *_right = nullptr;

        void ReturnDataVector(std::vector<Data>& vector);
        void LoopForLinesConnection(std::vector<QPoint>& vec);
        void SetDataForDrawing(Node& root);
        void SetPos(int& pos);
        void SetLevel(int& level);
    };
}
