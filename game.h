#ifndef GAME_H //Начало
#define GAME_H //Начало

#include <QWidget> //Начало
#include <QVector>
#include <QPoint>
#include <QKeyEvent>

class Game: public QWidget //Начало
{ //Начало
public: //Начало
    Game(); //Начало

protected:
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void paintEvent(QPaintEvent *e) override;//Отрисовка виджета

private:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int FIELD_WIDTH = 20;
    static const int FIELD_HEIGHT = 20;
    static const int DELAY = 200; //Обновление времени

    void doDrawing();
    void LocalApple();
    void move();
    void check_field();
    void gameOver();
    void check_apple();

    int timerID;

    bool m_inGame;

    QVector<QPoint> m_dots;//Положение ячеек змейки
    QPoint m_apple;//Положение яблока

    void initGame();

    enum Direction{//Направление движения змейки
        right, left, up, down
    };

    Direction m_dir;





}; //Начало

#endif // GAME_H Начало
