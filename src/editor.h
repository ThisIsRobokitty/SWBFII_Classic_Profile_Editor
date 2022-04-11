#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <string>
#include <QObject>
using namespace std;

#define numberofbytesinfile 4356 // last offset 4356=0x1104
#define medalsstart 1404 // 0x57c
#define medalsend 1422 // 0x58d
#define statsstart 3980 // 0xf8c
#define statend 3992 // 0xf97

class Editor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString dialogTitle READ dialogTitle)
    Q_PROPERTY(QString dialogText READ dialogText)
    Q_PROPERTY(long long gunslinger READ gunslinger WRITE setGunslinger NOTIFY gunslingerChanged)
    Q_PROPERTY(long long frenzy READ frenzy WRITE setFrenzy NOTIFY frenzyChanged)
    Q_PROPERTY(long long demolition READ demolition WRITE setDemolition NOTIFY demolitionChanged)
    Q_PROPERTY(long long technician READ technician WRITE setTechnician NOTIFY technicianChanged)
    Q_PROPERTY(long long marksman READ marksman WRITE setMarksman NOTIFY marksmanChanged)
    Q_PROPERTY(long long regulator READ regulator WRITE setRegulator NOTIFY regulatorChanged)
    Q_PROPERTY(long long endurance READ endurance WRITE setEndurance NOTIFY enduranceChanged)
    Q_PROPERTY(long long guardian READ guardian WRITE setGuardian NOTIFY guardianChanged)
    Q_PROPERTY(long long hero READ hero WRITE setHero NOTIFY heroChanged)
    Q_PROPERTY(long long points READ points WRITE setPoints NOTIFY pointsChanged)
    Q_PROPERTY(long long kills READ kills WRITE setKills NOTIFY killsChanged)
    Q_PROPERTY(long long deaths READ deaths WRITE setDeaths NOTIFY deathsChanged)
public:
    explicit Editor(QObject *parent = nullptr);
    QString name() { return m_name; };
    QString dialogTitle() { return m_dialogTitle; };
    QString dialogText() { return m_dialogText; };
    long long gunslinger() { return m_gunslinger; };
    long long frenzy() { return m_frenzy; };
    long long demolition() { return m_demolition; };
    long long technician() { return m_technician; };
    long long marksman() { return m_marksman; };
    long long regulator() { return m_regulator; };
    long long endurance() { return m_endurance; };
    long long guardian() { return m_guardian; };
    long long hero() { return m_hero; };
    long long points() { return m_points; };
    long long kills() { return m_kills; };
    long long deaths() { return m_deaths; };

public slots:
    void setName(QString name);
    void setGunslinger(long long gunslinger);
    void setFrenzy(long long frenzy);
    void setDemolition(long long demolition);
    void setTechnician(long long technician);
    void setMarksman(long long marksman);
    void setRegulator(long long regulator);
    void setEndurance(long long endurance);
    void setGuardian(long long guardian);
    void setHero(long long hero);
    void setPoints(long long points);
    void setKills(long long kills);
    void setDeaths(long long deaths);

    void readFile(QString profilePath);
    void saveFile(QString profilePath);
    void backupfile(QString profilePath);

signals:
    void nameChanged(QString newValue);
    void gunslingerChanged(long long newValue);
    void frenzyChanged(long long newValue);
    void demolitionChanged(long long newValue);
    void technicianChanged(long long newValue);
    void marksmanChanged(long long newValue);
    void regulatorChanged(long long newValue);
    void enduranceChanged(long long newValue);
    void guardianChanged(long long newValue);
    void heroChanged(long long newValue);
    void pointsChanged(long long newValue);
    void killsChanged(long long newValue);
    void deathsChanged(long long newValue);
    void showMessageBox();

private:
    QString  selectedPath {""};
    QString  m_name {""};
    QString  m_dialogText {""};
    QString  m_dialogTitle {""};
    long long m_gunslinger {0} ;
    long long m_frenzy {0} ;
    long long m_demolition {0} ;
    long long m_technician {0} ;
    long long m_marksman {0} ;
    long long m_regulator {0} ;
    long long m_endurance {0} ;
    long long m_guardian {0} ;
    long long m_hero {0} ;
    long long m_points {0} ;
    long long m_kills {0} ;
    long long m_deaths {0} ;

    string p1, stats_p1;
    string p3, stats_p3;
    uint16_t umed[9];
    uint32_t stats_umed[3];
};

#endif // EDITOR_H
