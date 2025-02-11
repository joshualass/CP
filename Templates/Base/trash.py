import chess

def is_legal_position(board):
    white_king_square = None
    black_king_square = None
    white_pawn_square = None
   
    # Find piece positions
    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            if piece.piece_type == chess.KING:
                if piece.color == chess.WHITE:
                    white_king_square = square
                else:
                    black_king_square = square
            elif piece.piece_type == chess.PAWN:
                white_pawn_square = square
   
    # Kings must be at least 1 square apart
    if chess.square_distance(white_king_square, black_king_square) <= 1:
        return False
   
    # White pawn can't be behind white king (impossible to reach)
    # white_king_rank = white_king_square // 8
    # white_pawn_rank = white_pawn_square // 8
    # if white_pawn_rank <= white_king_rank:

    #     return False
   
    # Check if either king is in check in the current position
    return not board.is_check()
board = chess.Board()
board.clear()  # Start with empty board

pieces = [chess.Piece(chess.PAWN, chess.WHITE),
          chess.Piece(chess.KING, chess.BLACK),
          chess.Piece(chess.KING, chess.WHITE)]

count = 0

for i in range(64):
    # Skip first and last ranks for pawn
    if i < 8 or i > 55:
        continue
    for j in range(64):
        if j == i:
            continue
        for k in range(64):
            if k == i or k == j:
                continue
           
            # Set up the position
            board.clear()
            piece_map = {k:v for k, v in zip((i, j, k), pieces)}
            board.set_piece_map(piece_map)
           
            # Check both turns only if position is legal
            if is_legal_position(board):
                for turn in (chess.WHITE, chess.BLACK):
                    board.turn = turn
                    if board.is_stalemate():
                        print("board\n",board,sep='')
                        count += 1

print(count)