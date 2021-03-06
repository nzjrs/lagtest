#include "timemodel.h"

#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

#include <QElapsedTimer>

TimeModel::TimeModel()
    : cpCnt(0), gain(0), offset(0) , timer(0)
{
    init();
}

void TimeModel::init()
{
    this->timer = new QElapsedTimer();
    timer->start();

    this->A = MatrixXd::Ones(TimeModel::clockHistory, 2);
    this->b = VectorXd::Ones( TimeModel::clockHistory );
}

void TimeModel::start()
{
    if(timer) delete timer;

    this->init();
}

//Return time [ns] since program start
double TimeModel::getCurrentTime()
{
    return (double) this->timer->nsecsElapsed();
}

double TimeModel::toLocalTime( adcMeasurement adc)
{
    double arduinoClock = adc.arduino_epoch*(1<<16) + adc.arduino_ticks;
    return arduinoClock*this->gain + this->offset;
}

void TimeModel::update(clockPair cp)
{
    double arduinoClock = cp.arduino_epoch*(1<<16) + cp.arduino_ticks;

    cpCnt = (cpCnt + 1) % this->clockHistory ;
    this->A(this->cpCnt, 0) = arduinoClock;
    this->b(this->cpCnt) = cp.local;

    this->x = A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b);

    this->gain = x(0); this->offset = x(1);
    //qDebug("TimdeModel: gain %g, offset %g , #n ClockPairs %d", gain, offset, cpCnt);

    // Print the matrix and a test
    //cout << "A: " << A << endl;
    //cout << "b: " << b << endl;
    //cout << "x: " << x << endl;
    //qDebug("Test %g -> %g", arduinoClock, arduinoClock*gain + offset );
}


//void updateModel()

/*
 * Has to be close to this python result
In [77]: A
Out[77]:
array([[ 100.,    1.],
       [ 110.,    1.],
       [ 122.,    1.],
       [ 135.,    1.],
       [ 141.,    1.]])

In [78]: b
Out[78]:
array([[ 20.],
       [ 22.],
       [ 25.],
       [ 29.],
       [ 30.]])

In [79]: x,resids,rank,s = np.linalg.lstsq(A,b)

In [80]: x
Out[80]:
array([[ 0.25354303],
       [-5.63083305]])
*/

void TimeModel::testModelGenerator()
{
    MatrixXd A = MatrixXd::Ones(5, 2);
    A(0,0) = 100.0;
    A(1,0) = 110.0;
    A(2,0) = 122.0;
    A(3,0) = 135.0;
    A(4,0) = 141.0;

    VectorXd b = VectorXd(5);
    b(0) = 20.0;
    b(1) = 22.0;
    b(2) = 25.0;
    b(3) = 29.0;
    b(4) = 30.0;

    cout << A << endl << b;

    cout << "The least-squares solution is:\n";
    VectorXd x = VectorXd(5);

    double d;
    d = this->getCurrentTime() ;
    cout << "\nTIME:" << d << endl;

    x = A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b);
    //x = A.colPivHouseholderQr().solve(b);

    d = this->getCurrentTime() ;
    cout << "\nTIME:" << d << endl;

    cout << endl << x << endl;

    //Test the result
    cout << A*x;

    d = this->getCurrentTime() ;
    cout << "\nTIME:" << d << endl;
}


