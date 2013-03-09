#ifndef PLAYER_H
#define PLAYER_H

#include <QHostAddress>

class Player
{
private:
	QHostAddress address;

public:
	explicit Player(const QHostAddress &address);
};

#endif // PLAYER_H
