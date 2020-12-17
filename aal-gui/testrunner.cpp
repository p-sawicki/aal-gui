#include "testrunner.h"

TestRunner::TestRunner(QObject *parent) : TestRunner(0,0,0,0,0, parent) {}

TestRunner::TestRunner(int mn, int mx, int st, int r, int sel, QObject *parent) : QThread(parent),
    m_min(mn), m_max(mx), m_step(st), m_repeats(r), m_algorithm(sel) {
}

void TestRunner::run()
{
    running = true;
    for (int bricks = m_min; running && bricks <= m_max; bricks += m_step) {
        double average_duration = 0;
        for (int i = 0; running && i < m_repeats; ++i) {
            auto stream = std::stringstream();
            generate(bricks, 1, bricks, stream);

            auto start = std::chrono::steady_clock::now();
            switch (m_algorithm) {
            case 0:
                get_highest_tower(stream);
                break;
            case 1:
                graph_get_highest_tower(stream);
                break;
            case 2:
                bf_get_highest_tower(stream);
                break;
            }
            auto end = std::chrono::steady_clock::now();
            average_duration += std::chrono::duration<double>(end - start).count() / m_repeats;
        }
        emit updated(this, bricks, average_duration);
    }
    emit finished();
}

void TestRunner::cancel() {
    running = false;
}
