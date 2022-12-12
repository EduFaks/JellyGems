#pragma once

namespace NetPacket {
	void FullClientPacket(Client& Player, sf::Packet& InitialPacket);
	void GameClientPacket(Client& Player, sf::Packet& ClientPacket);

	void InitialPacketUpdate(Client* Players, sf::Packet& InitialPacket);
	void InGamePacket(Client* Players, sf::Packet& InGamePacet);
}