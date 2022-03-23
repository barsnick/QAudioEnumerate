// bad example from https://ask.fedoraproject.org/t/qt-audio-help/5448

/*
 *
 *
 */

#include <QCoreApplication>
#include "AudioEnumerator.hpp"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	AudioEnumerator recorder;
	return a.exec();
}
