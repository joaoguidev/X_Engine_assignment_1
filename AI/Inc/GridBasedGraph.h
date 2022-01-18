#pragma once

namespace AI
{
	class GridBasedGraph
	{
	public:
		enum Direction // enums are basically numbers with names
		{
			North, // 0
			South,
			East,
			West,
			NorthEast,
			NorthWest,
			SouthEast,
			SouthWest
		};

		struct Node
		{
			std::array<Node*, 8> neighbors = {};
			int columns = 0;
			int row = 0;
		};

		void Initialize(int columns, int rows);

		Node* GetNode(int column, int row);
		const Node* GetNode(int column, int row) const;

		int GetColumns() const { return mColumns; }
		int GetRows() const { return mRows; }

	private:
		int GetIndex(int column, int row) const;

		std::vector<Node> mNodes;
		int mColumns = 0;
		int mRows = 0;
	};
}