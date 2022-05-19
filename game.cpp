#include "game.h" //Начало
#include <QDebug>
#include <QPainter>
#include <QTime>
#include <QMessageBox>

//.............
//Конструктор
Game::Game() //Начало
{ //Начало
    this->resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);//Размеры формы

    this->setWindowTitle("Snake game");//Заголовок формы

    initGame();

}

//..............
//Функции
void Game::timerEvent(QTimerEvent *e) //Метод зависящий от времени
{
    Q_UNUSED(e);

    if(m_inGame){
        check_apple();
        move();
        check_field();

    }
    else{
        killTimer(timerID);//Остановка таймера
        gameOver();
    }

    this->repaint();//Мы просим перерисовать всё
}

void Game::keyPressEvent(QKeyEvent *e) //Здесь обрабатываем нажатие любой клавиши
{
    int key = e->key();

    if (key == Qt::Key_Left && m_dir != Direction::right){m_dir = Direction::left;}
    if (key == Qt::Key_Right && m_dir != Direction::left){m_dir = Direction::right;}
    if (key == Qt::Key_Up && m_dir != Direction::down)   {m_dir = Direction::up;}
    if (key == Qt::Key_Down && m_dir != Direction::up)   {m_dir = Direction::down;}

}

void Game::paintEvent(QPaintEvent *e)//Отрисовка виджета
{
    Q_UNUSED(e);//Чтобы пропали восклицательные знаки из-за *e
    doDrawing();
}

void Game::doDrawing()//Функция рисования(яблока и змейки) и движения змейки
{
    QPainter qp(this);

    if(m_inGame){

        qp.setPen(Qt::red);//Цвет рамки
        qp.setBrush(Qt::green);//Заливка qp
        qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);//Рисуем фигуру
        for(int i = 0; i < m_dots.size(); i++){
            if(i == 0){
                qp.setBrush(Qt::white);
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
            else{
                qp.setBrush(Qt::yellow);
                qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
            }
        }

    }
    else{
        //gameOver()
    }
}

void Game::LocalApple()//Задаёт рандомные координаты
{
    QTime time = QTime::currentTime();//Для привязки ко времени
    srand((uint) time.msec());//Для привязки ко времени

    m_apple.rx() = rand() % DOT_WIDTH;
    m_apple.ry() = rand() % DOT_HEIGHT;
}

void Game::move() //Задаётся направление змейки и движение хвоста
{
    for(int i = m_dots.size()-1; i>0; --i){
        m_dots[i] = m_dots[i-1];
    }
    switch (m_dir){
    case left: {m_dots[0].rx() -= 1; break; }
    case right: {m_dots[0].rx() += 1; break; }
    case up: {m_dots[0].ry() -= 1; break; }
    case down: {m_dots[0].ry() += 1; break; }
    }

}

void Game::check_field()//Проверка, что змейка не врезалась сама в себя и выход за поле
{
    if(m_dots.size() > 4){ //Проверка на столкновение
        for (int i = 1; i < m_dots.size(); i++){
            if(m_dots[0] == m_dots[i]){
                m_inGame = false;
            }
        }
    }

    if(m_dots[0].x() < 0 || m_dots[0].x() >= FIELD_WIDTH || m_dots[0].y() < 0 || m_dots[0].y() >= FIELD_HEIGHT ){
        m_inGame = false;
    }

}

void Game::gameOver()
{
    QMessageBox msgb;
    msgb.setText("Game Over!");
    msgb.exec();

    initGame();

}

void Game::check_apple()//Проверка съедание яблока
{
    if(m_dots[0] == m_apple){
        m_dots.push_back(QPoint(0,0));
        LocalApple();
    }
}

void Game::initGame()//Инициализация змейки
{
    m_inGame = true;
    m_dir = right;

    m_dots.resize(3);

    for(int i = 0; i < m_dots.size(); ++i){
        m_dots[i].rx() = m_dots.size() - i;
        m_dots[i].ry() = 0;
    }

    LocalApple();

    timerID = startTimer(DELAY);
}
