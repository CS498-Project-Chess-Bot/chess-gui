#include "chess_board_2D.hpp"

ChessBoardModel2D::ChessBoardModel2D(bool isPlayerWhite) 
    : m_isPlayerWhite(isPlayerWhite)
{
    Ref<VertexBuffer> vbo = createRef<VertexBuffer>(TILE_QUAD_VERTICES);
    BufferLayout layout = {
        BufferElement(ShaderDataType::Float3, "Position")
    };
    vbo->setLayout(layout);

    Ref<IndexBuffer> ibo = createRef<IndexBuffer>(TILE_QUAD_INDICES);

    m_VAO = createRef<VertexArray>();
    m_VAO->addVertexBuffer(vbo);
    m_VAO->setIndexBuffer(ibo);

    m_shader = createRef<Shader>("shaders/chess_board.vs", "shaders/chess_board.fs");

    std::vector<ChessPieceType> boardState = m_gameBoard.getBoardState();
    for(int y = 0; y < CHESS_ROWS; y++) {
        for(int x = 0; x < CHESS_COLS; x++) {
            bool isWhite = ((y*8)+x+(y%2))%2;
            Ref<ChessTileModel2D> tile = createRef<ChessTileModel2D>(isWhite);

            int xLoc = isPlayerWhite ? x : CHESS_COLS-x-1;
            int yLoc = isPlayerWhite ? y : CHESS_ROWS-y-1;
            tile->transform().changePos({xLoc*1.0f, yLoc*1.0f, -8.0f});

            int idx = 8*y + x;
            if(boardState[idx] != ChessPieceType::none){
                Ref<ChessPieceModel2D> piece = createRef<ChessPieceModel2D>(boardState[idx]);
                tile->addChild(piece);
            }
            m_children.push_back(tile);
        }
    }
}

ChessBoardModel2D::~ChessBoardModel2D() {

}

bool ChessBoardModel2D::tryMove(Move m) {
    MoveResult res = m_gameBoard.makeMove(m);
    if(res != MoveResult::Invalid) {
        int startX = std::get<0>(m.getStartTile());
        int startY = std::get<1>(m.getStartTile());
        int endX = std::get<0>(m.getEndTile());
        int endY = std::get<1>(m.getEndTile());
        ChessPieceType piece = m.getPieceType();

        int startIdx = startY * CHESS_ROWS + startX;
        int endIdx = endY * CHESS_ROWS + endX;

        m_children[endIdx]->getChildren().clear();
        m_children[endIdx]->addChild(m_children[startIdx]->getChildren().front());
        m_children[startIdx]->getChildren().clear();

        if(res == MoveResult::Castle) {
            if(piece == ChessPieceType::white_king && startX > endX) {
                int rookLoc = 0*CHESS_ROWS + 0;
                m_children[endIdx+1]->addChild(m_children[rookLoc]->getChildren().front());
                m_children[rookLoc]->getChildren().clear();
            }
            else if(piece == ChessPieceType::white_king && startX < endX) {
                int rookLoc = 0*CHESS_ROWS + CHESS_COLS-1;
                m_children[endIdx-1]->addChild(m_children[rookLoc]->getChildren().front());
                m_children[rookLoc]->getChildren().clear();
            }
            else if(piece == ChessPieceType::black_king && startX > endX) {
                int rookLoc = (CHESS_ROWS-1)*CHESS_ROWS + 0;
                m_children[endIdx+1]->addChild(m_children[rookLoc]->getChildren().front());
                m_children[rookLoc]->getChildren().clear();
            }
            else if(piece == ChessPieceType::black_king && startX < endX) {
                int rookLoc = (CHESS_ROWS-1)*CHESS_ROWS + CHESS_COLS-1;
                m_children[endIdx-1]->addChild(m_children[rookLoc]->getChildren().front());
                m_children[rookLoc]->getChildren().clear();
            }
        }

        if(res == MoveResult::EnPassant){
            if(piece == ChessPieceType::white_pawn){
                m_children[endIdx-8]->getChildren().clear();
            }else{
                m_children[endIdx+8]->getChildren().clear();
            }
        }

        if(res == MoveResult::Promotion){
            ChessPieceType pieceToPromoteTo;
            int x;
            while(true){
                std::cout << "What piece do you want? 1 - Queen, 2 - Rook, 3 - Bishop, 4 - Knight";
                std::cin >> x;
                switch(x){
                    case 1:
                        if(piece == ChessPieceType::white_pawn) {
                            pieceToPromoteTo = ChessPieceType::white_queen;
                        }else{
                            pieceToPromoteTo = ChessPieceType::black_queen;
                        }
                        break;
                    case 2:
                        if(piece == ChessPieceType::white_pawn) {
                            pieceToPromoteTo = ChessPieceType::white_rook;
                        }else{
                            pieceToPromoteTo = ChessPieceType::black_rook;
                        }
                        break;
                    case 3:
                        if(piece == ChessPieceType::white_pawn) {
                            pieceToPromoteTo = ChessPieceType::white_bishop;
                        }else{
                            pieceToPromoteTo = ChessPieceType::black_bishop;
                        }
                        break;
                    case 4:
                        if(piece == ChessPieceType::white_pawn) {
                            pieceToPromoteTo = ChessPieceType::white_knight;
                        }else{
                            pieceToPromoteTo = ChessPieceType::black_knight;
                        }
                        break;
                    default:
                        continue;
                }
                break;
            }
            m_gameBoard.setBoardStateAt(endX, endY, pieceToPromoteTo);
            m_children[endIdx]->getChildren().clear();
            Ref<ChessPieceModel2D> promotesTo = createRef<ChessPieceModel2D>(pieceToPromoteTo);
            m_children[endIdx]->addChild(promotesTo);
        }

    }
    return res != MoveResult::Invalid;
}

bool ChessBoardModel2D::getHitTile(Camera& cam, glm::vec3 rayDir, int* x, int* y) {
    for(size_t idx = 0; idx < m_children.size(); idx++) {
        auto tile = std::dynamic_pointer_cast<ChessTileModel2D>(m_children[idx]);
        if(!tile) {
            CORE_ASSERT(false, "One of chess board's tiles is not an actual tile!");
            return false;
        }
        bool hits = tile->checkRayIntersectsTile(cam.pos(), rayDir);
        if(hits) {
            *x = (int)idx % CHESS_COLS;
            *y = (int)idx / CHESS_ROWS;
            return true;
        }
    }
    return false;
}

void ChessBoardModel2D::setTileHightlight(int x, int y, bool b) {
    if( x < 0 || x > CHESS_COLS-1 || y < 0 || y > CHESS_ROWS-1)
        CORE_ASSERT(false, "Invalid tile coords!");

    Ref<ChessTileModel2D> tile = std::dynamic_pointer_cast<ChessTileModel2D>(m_children[y*CHESS_ROWS + x]);
    tile->setHighlight(b);
}