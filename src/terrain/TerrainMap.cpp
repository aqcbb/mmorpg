#include "terrain/TerrainMap.h"
#include "terrain/types/Plains.h"
#include <stdexcept>

TerrainMap::TerrainMap(int width, int height, std::shared_ptr<ILogger> logger) : width_(width), height_(height), logger_(logger) {
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

	if (logger_) {
		logger_->log(LogEvent("INFO", "ENV", "Terrain changed at (" + std::to_string(x) + "," + std::to_string(y) + ") to " + terrain->getSymbol()));
	}
}

bool TerrainMap::inBounds(int x, int y) const {
	return x >= 0 && x < width_ && y >= 0 && y < height_;
}