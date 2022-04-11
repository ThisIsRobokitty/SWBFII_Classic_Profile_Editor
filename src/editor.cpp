#include "editor.h"
#include <QFileInfo>
#include <QUrl>
#include <QDir>

using namespace std;

Editor::Editor(QObject* parent) : QObject(parent)
{
    if(QFileInfo::exists("default.profile")){
        readFile("default.profile");
    }
    selectedPath = QDir::currentPath() + '/';
}

void Editor::setName(QString value)
{
    if (value == m_name)
        return;
    m_name = value;
    emit nameChanged(value);
}

void Editor::setGunslinger(long long value)
{
    if (value == m_gunslinger)
        return;
    m_gunslinger = value;
    umed[0] = value;
    emit gunslingerChanged(value);
}

void Editor::setFrenzy(long long value)
{
    if (value == m_frenzy)
        return;
    m_frenzy = value;
    umed[1] = value;
    emit frenzyChanged(value);
}

void Editor::setDemolition(long long value)
{
    if (value == m_demolition)
        return;
    m_demolition = value;
    umed[2] = value;
    emit demolitionChanged(value);
}

void Editor::setTechnician(long long value)
{
    if (value == m_technician)
        return;
    m_technician = value;
    umed[3] = value;
    emit technicianChanged(value);
}

void Editor::setMarksman(long long value)
{
    if (value == m_marksman)
        return;
    m_marksman = value;
    umed[4] = value;
    emit marksmanChanged(value);
}

void Editor::setRegulator(long long value)
{
    if (value == m_regulator)
        return;
    m_regulator = value;
    umed[5] = value;
    emit regulatorChanged(value);
}

void Editor::setEndurance(long long value)
{
    if (value == m_endurance)
        return;
    m_endurance = value;
    umed[6] = value;
    emit enduranceChanged(value);
}

void Editor::setGuardian(long long value)
{
    if (value == m_guardian)
        return;
    m_guardian = value;
    umed[7] = value;
    emit guardianChanged(value);
}

void Editor::setHero(long long value)
{
    if (value == m_hero)
        return;
    m_hero = value;
    umed[8] = value;
    emit heroChanged(value);
}

void Editor::setPoints(long long value)
{
    if (value == m_points)
        return;
    m_points = value;
    stats_umed[0] = value;
    emit pointsChanged(value);
}

void Editor::setKills(long long value) {
    if (value == m_kills)
        return;
    m_kills = value;
    stats_umed[1] = value;
    emit killsChanged(value);
}

void Editor::setDeaths(long long value)
{
    if (value == m_deaths)
        return;
    m_deaths = value;
    stats_umed[2] = value;
    emit deathsChanged(value);
}

void Editor::readFile(QString profilePath)
{
    selectedPath = profilePath;
    backupfile(profilePath.replace("file:///", ""));

    std::string filename = profilePath.replace("file:///", "").toLocal8Bit().constData();
    ifstream inFile;
    size_t size = 0;

    inFile.open(filename, ios::in | ios::binary | ios::ate);

    inFile.seekg(0, ios::end); // set the pointer to the end
    size = inFile.tellg(); // get the length of the file
    inFile.seekg(0, ios::beg); // set the pointer to the beginning

    string fullfile;
    fullfile.reserve(size);
    fullfile.assign((istreambuf_iterator<char>(inFile)),
        istreambuf_iterator<char>());

    string medals, stats;

    p1 = fullfile.substr(0, medalsstart);
    medals = fullfile.substr(medalsstart, medalsend - medalsstart);
    p3 = fullfile.substr(medalsend);

    stats_p1 = fullfile.substr(0, statsstart);
    stats = fullfile.substr(statsstart, statend - statsstart);
    stats_p3 = fullfile.substr(statend);

    inFile.close();

    char const *c = medals.c_str();
    char const *stats_c = stats.c_str();

    for (int k = 0; k < 9; k++) {
        umed[k] = ((uint8_t)c[k*2+1] << 8) | (uint8_t)c[k*2];
    }

    for (int k = 0; k < 3; k++) {
        stats_umed[k] = ((uint8_t)stats_c[k * 4 + 3] << 24) | ((uint8_t)stats_c[k * 4 + 2] << 16) | ((uint8_t)stats_c[k * 4 + 1] << 8) | (uint8_t)stats_c[k * 4];
    }

    setGunslinger(umed[0]);
    setFrenzy(umed[1]);
    setDemolition(umed[2]);
    setTechnician(umed[3]);
    setMarksman(umed[4]);
    setRegulator(umed[5]);
    setEndurance(umed[6]);
    setGuardian(umed[7]);
    setHero(umed[8]);

    setPoints(stats_umed[0]);
    setKills(stats_umed[1]);
    setDeaths(stats_umed[2]);
}

void Editor::saveFile(QString profilePath)
{
    if (profilePath == ""){
        if (m_name == ""){
            m_dialogText = "Please input profile name.";
            m_dialogTitle = "Error!";
            emit showMessageBox();
            return;
        }
        QString basename = QUrl(selectedPath).fileName();
        profilePath = selectedPath.remove(basename) + m_name + ".profile";
    }else{
        selectedPath = profilePath;
    }

    std::string filename = profilePath.replace("file:///", "").toLocal8Bit().constData();
    ofstream writeFile(filename, ios::out | ios::binary);

    if (writeFile.is_open())
    {
        // write medal data
        char b[18];
        for (int j = 0; j < 9; j++) {
            b[j * 2] = (char)(umed[j] & 0xFF);
            b[j * 2 + 1] = (char)(umed[j] >> 8);
        }

        string newMedals(b, 18);
        newMedals.resize(18);
        string newData = p1 + newMedals + p3;

        stats_p1 = newData.substr(0, statsstart);
        stats_p3 = newData.substr(statend);
        // write state data
        char stats_b[12];

        for (int j = 0; j < 3; j++) {
            stats_b[j * 4] = (char)(stats_umed[j] & 0xFFFFFF);
            stats_b[j * 4 + 1] = (char)(stats_umed[j] >> 8);
            stats_b[j * 4 + 2] = (char)(stats_umed[j] >> 16);
            stats_b[j * 4 + 3] = (char)(stats_umed[j] >> 24);
        }

        string newStats(stats_b, 12);
        newStats.resize(12); // remove extraneous data
        string stats_newData = stats_p1 + newStats + stats_p3;

        writeFile << stats_newData;

        m_dialogText = "Profile saved successfully!\n" + profilePath.replace("file:///", "");
        m_dialogTitle = "Saved!";
        emit showMessageBox();
    }
    else
    {
        m_dialogText = "Bad filename or other error.";
        m_dialogTitle = "Error!";
        emit showMessageBox();
    }
    writeFile.close();
}

void Editor::backupfile(QString profilePath)
{
    std::string line = profilePath.toLocal8Bit().constData();

    ifstream source(line, ios::binary);
    ofstream dest(line + ".bak", ios::binary);

    // file size
    source.seekg(0, ios::end);
    ifstream::pos_type size = source.tellg();
    source.seekg(0);
    // allocate memory for buffer
    char* buffer = new char[size];

    // copy file
    source.read(buffer, size);
    dest.write(buffer, size);

    // clean up
    delete[] buffer;
    source.close();
    dest.close();
}
