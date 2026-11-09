#include "terrain/TerrainMap.h"
#include "terrain/types/Plains.h"
#include <stdexcept>

TerrainMap::TerrainMap(int width, int height) : width_(width), height_(height) {
	if (width <= 0 || height <= 0) throw std::invalid_argument("TerrainMap dimensions must be positive");

	grid_.resize(height_);
	for (int y = 0; y < height; ++y) {
		grid_[y].resize(width_);
		for (int x = 0; x < width; ++x) {
			auto plains = std::make_shared<Plains>();
			grid_[y][x] = std::make_shared<TerrainProxy>(plains);
		}
	}
}

std::shared_ptr<Terrain> TerrainMap::getTerrainAt(int x, int y) const {
	if (!inBounds(x, y)) throw std::out_of_range("TerrainMap: coordinates out of bounds");
	return grid_[y][x];
}

void TerrainMap::setTerrainAt(int x, int y, std::shared_ptr<Terrain> terrain) {
	if (!inBounds(x, y)) throw std::out_of_range("TerrainMap: coordinates out of bounds");
	grid_[y][x] = std::make_shared<TerrainProxy>(terrain);
}

bool TerrainMap::inBounds(int x, int y) const {
	return x >= 0 && x < width_ && y >= 0 && y < height_;
}