#ifndef GAME_H //������
#define GAME_H //������

#include <QWidget> //������
#include <QVector>
#include <QPoint>
#include <QKeyEvent>

class Game: public QWidget //������
{ //������
public: //������
    Game(); //������

protected:
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;//��������� �������

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 200; //���������� �������

    void doDrawing();
    void LocalApple();
    void move();
    void check_field();
    void gameOver();
    void check_apple();

    int timerID;

    bool m_inGame;

    QVector<QPoint> m_dots;//��������� ����� ������
    QPoint m_apple;//��������� ������

    void initGame();

    enum Direction{//����������� �������� ������
        right, left, up, down
    };

    Direction m_dir;





}; //������

#endif // GAME_H ������
