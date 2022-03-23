#ifndef AUDIOENUMERTOR_HPP
#define AUDIOENUMERTOR_HPP

#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QTextStream>
#include <QAudioInput>
#include <QAudioOutput>
#include <QObject>

class AudioEnumerator : public QObject
{
    Q_OBJECT

public:
    AudioEnumerator();
	~AudioEnumerator();

private:
    QAudioFormat formatIn;
    QAudioFormat formatOut;

    QAudioInput *m_audioInput;
    QAudioOutput *m_audioOutput;

    QAudioDeviceInfo m_InputDevice;
    QAudioDeviceInfo m_OutputDevice;

    QIODevice *m_input;
    QIODevice *m_output;

    QAudioDeviceInfo deviceIn;
    QAudioDeviceInfo deviceOut;

	void dumpAudioDeviceInfo(const QAudioDeviceInfo &deviceInfo);
    void getFormat();
    void createAudioInput();
    void createAudioOutput();
    void beginAudio();
};

#endif // AUDIOENUMERTOR_HPP
