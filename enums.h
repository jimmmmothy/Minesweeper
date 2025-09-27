#pragma once
enum CellState {
    UNOPENED, FLAGGED, MINE, BLAST, NUMBER, FALSE
};

enum FieldType {
    PRIV, PUBLIC, LOST
};

enum GameOverState {
    WIN, LOSE
};
