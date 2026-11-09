#pragma once
#include "Terrain.h"
#include "TerrainProxy.h"
#include <vector>
#include <memory>

class TerrainMap {
private:
	int width_;
	int height_;
	std::vector<std::vector<std::shared_ptr<TerrainProxy>>> grid_;
public:
	TerrainMap(int width, int height);

	std::shared_ptr<Terrain> getTerrainAt(int x, int y) const;

	void setTerrainAt(int x, int y, std::shared_ptr<Terrain> terrain);

	int getWidth() const { return width_; }
	int getHeight() const { return height_; }
	bool inBounds(int x, int y) const;
};