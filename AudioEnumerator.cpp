#include "AudioEnumerator.hpp"

AudioEnumerator::AudioEnumerator() {
    QTextStream(stdout) << "running" << endl;
    getFormat();
    createAudioInput();
    createAudioOutput();
    QTextStream(stdout) << "initialized" << endl;
}

AudioEnumerator::~AudioEnumerator() {
    delete m_audioInput;
    delete m_audioOutput;
}

void AudioEnumerator::dumpAudioDeviceInfo(const QAudioDeviceInfo &deviceInfo) {
    QTextStream out(stdout);
    // QStringList stringList;

    out << "Audio device: " << deviceInfo.deviceName() << endl;
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    out << "  Realm: " << deviceInfo.realm() << endl;
#endif
    out << "  Channel counts:";
    for (auto channelCount: deviceInfo.supportedChannelCounts()) {
        out << " " << channelCount << ",";
    }
    out << endl;

    out << "  Sample sizes:";
    for (auto sampleSize: deviceInfo.supportedSampleSizes()) {
        out << " " << sampleSize << ",";
    }
    out << endl;

    out << "  Sample rates:";
    for (auto sampleRate: deviceInfo.supportedSampleRates()) {
        out << " " << sampleRate << ",";
    }
    out << endl;
}

void AudioEnumerator::getFormat() {
    formatIn.setSampleSize(8);
    formatIn.setCodec("audio/pcm");
    formatIn.setByteOrder(QAudioFormat::LittleEndian);
    formatIn.setSampleType(QAudioFormat::UnSignedInt);

    // QAudioDeviceInfo deviceIn = QAudioDeviceInfo::defaultInputDevice();
    auto indevs = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    for (auto dev: indevs) {
        dumpAudioDeviceInfo(dev);
    }
    if (!indevs.empty()) {
        deviceIn = indevs.at(0);
        if (!deviceIn.isFormatSupported(formatIn)) {
            QTextStream(stdout) << " default formatIn not supported" << endl;
            formatIn = deviceIn.nearestFormat(formatIn);
        } else {
            QTextStream(stdout) << " default formatIn supported" << endl;
        }
    } else {
        QTextStream(stdout) << " no in devices found" << endl;
    }

    // QAudioDeviceInfo deviceOut = QAudioDeviceInfo::defaultOutputDevice();
    auto outdevs = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    for (auto dev: outdevs) {
        dumpAudioDeviceInfo(dev);
    }
    if (!outdevs.empty()) {
        deviceOut = outdevs.at(0);
        if (!deviceOut.isFormatSupported(formatOut)) {
            QTextStream(stdout) << "1. default formatOut not supported " << endl;
            formatOut = deviceOut.nearestFormat(formatOut);
        }
    } else {
        QTextStream(stdout) << " no out devices found" << endl;
    }
}


void AudioEnumerator::createAudioInput() {
    m_audioInput = new QAudioInput(m_InputDevice, formatIn);
}

void AudioEnumerator::createAudioOutput() {
    m_audioOutput = new QAudioOutput(m_OutputDevice, formatOut);
}

void AudioEnumerator::beginAudio() {
    m_output = m_audioOutput->start();
    m_input = m_audioInput->start();
}
