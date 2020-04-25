#include "autosave.h"
#include <QtCore>
#include <QDebug>
#include <time.h>
#include <ctime>

AutoSave::AutoSave()
{
}

void AutoSave::run()
{
    double sleepInterval = 60; // seconds
    while (true) {
        // save start time
        time_t startTime = time(NULL);

        // save the end time and elapsed time
        time_t endTime = time(NULL);
        double timeElapsed = difftime(endTime, startTime);

        // console output
        qDebug() << "Autosave finished: " << std::ctime(&endTime) << "Time elapsed: " << timeElapsed << "seconds.\n";

        // compute sleep time
        int sleepTime = (int)(sleepInterval - timeElapsed);

        // only sleep if sleepInterval hasn't been passed whilst saving
        if (0 < sleepTime){
            std::chrono::seconds sec(sleepTime);
            QThread::sleep(sleepTime);
        }
    }
}

