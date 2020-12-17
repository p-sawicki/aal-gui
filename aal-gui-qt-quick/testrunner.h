#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <QThread>
#include <sstream>
#include "aal/inc/gen.h"
#include "aal/inc/bf.h"
#include "aal/inc/dp.h"
#include "aal/inc/graph.h"

class TestRunner : public QThread
{
    Q_OBJECT
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(int step READ step WRITE setStep NOTIFY stepChanged)
    Q_PROPERTY(int repeats READ repeats WRITE setRepeats NOTIFY repeatsChanged)
    Q_PROPERTY(int algorithm READ algorithm WRITE setAlgorithm NOTIFY algorithmChanged)
public:
    TestRunner(QObject *parent = nullptr);
    TestRunner(int min, int max, int step, int repeats, int selected, QObject *parent = nullptr);
    void run();
    int min() const
    {
        return m_min;
    }

    int max() const
    {
        return m_max;
    }

    int step() const
    {
        return m_step;
    }

    int repeats() const
    {
        return m_repeats;
    }

    int algorithm() const
    {
        return m_algorithm;
    }

public slots:
    void setMin(int min)
    {
        if (m_min == min)
            return;

        m_min = min;
        emit minChanged(m_min);
    }

    void setMax(int max)
    {
        if (m_max == max)
            return;

        m_max = max;
        emit maxChanged(m_max);
    }

    void setStep(int step)
    {
        if (m_step == step)
            return;

        m_step = step;
        emit stepChanged(m_step);
    }

    void setRepeats(int repeats)
    {
        if (m_repeats == repeats)
            return;

        m_repeats = repeats;
        emit repeatsChanged(m_repeats);
    }

    void setAlgorithm(int algorithm)
    {
        if (m_algorithm == algorithm)
            return;

        m_algorithm = algorithm;
        emit algorithmChanged(m_algorithm);
    }

    void cancel();

signals:
    void updated(TestRunner *runner, int bricks, double time);
    void finished();
    void minChanged(int min);

    void maxChanged(int max);

    void stepChanged(int step);

    void repeatsChanged(int repeats);

    void algorithmChanged(int algorithm);

private:
    bool running;
    int m_min;
    int m_max;
    int m_step;
    int m_repeats;
    int m_algorithm;
};

#endif // TESTRUNNER_H
