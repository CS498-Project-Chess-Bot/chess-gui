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

            int saveDir = 0;
            if(piece == ChessPieceType::white_pawn){
                saveDir -= 8;
            }else{
                saveDir += 8;
            }

            std::cout << "checkpoint1" << std::endl;

            //save states of the 3 squares below before clearing and displaying promotion choices
            for(int i = 1; i < 4; i++){
                if (!m_children[endIdx + saveDir * i]->getChildren().empty())
                    saved[i-1] = m_children[endIdx + saveDir * i]->getChildren().front();
            }

            
            std::cout << "checkpoint2" << std::endl;

            for(int i = 0; i < 4; i++){
                m_children[endIdx + saveDir * i]->getChildren().clear();
            }


            if(piece == ChessPieceType::white_pawn){
                Ref<ChessPieceModel2D> wq = createRef<ChessPieceModel2D>(ChessPieceType::white_queen);
                Ref<ChessPieceModel2D> wr = createRef<ChessPieceModel2D>(ChessPieceType::white_rook);
                Ref<ChessPieceModel2D> wb = createRef<ChessPieceModel2D>(ChessPieceType::white_bishop);
                Ref<ChessPieceModel2D> wk = createRef<ChessPieceModel2D>(ChessPieceType::white_knight);

                m_children[endIdx]->addChild(wq);
                m_children[endIdx + saveDir]->addChild(wr);
                m_children[endIdx + saveDir * 2]->addChild(wb);
                m_children[endIdx + saveDir * 3]->addChild(wk);
            }else{
                Ref<ChessPieceModel2D> bq = createRef<ChessPieceModel2D>(ChessPieceType::black_queen);
                Ref<ChessPieceModel2D> br = createRef<ChessPieceModel2D>(ChessPieceType::black_rook);
                Ref<ChessPieceModel2D> bb = createRef<ChessPieceModel2D>(ChessPieceType::black_bishop);
                Ref<ChessPieceModel2D> bk = createRef<ChessPieceModel2D>(ChessPieceType::black_knight);

                m_children[endIdx]->addChild(bq);
                m_children[endIdx + saveDir]->addChild(br);
                m_children[endIdx + saveDir * 2]->addChild(bb);
                m_children[endIdx + saveDir * 3]->addChild(bk);
            }

            //flag app to handle promotion selection
            needsPromotionSelection = true;
        }
    }

    return res != MoveResult::Invalid;
}

void ChessBoardModel2D::promotePiece(int tileX, int tileY){
    
    //determine chosen piece
    ChessPieceType pieceChoice;
    switch(tileY){
        case 0:
            pieceChoice = ChessPieceType::black_queen;
            break;
        case 1:
            pieceChoice = ChessPieceType::black_rook;
            break;
        case 2:
            pieceChoice = ChessPieceType::black_bishop;
            break;
        case 3:
            pieceChoice = ChessPieceType::black_knight;
            break;
        case 4:
            pieceChoice = ChessPieceType::white_knight;
            break;
        case 5:
            pieceChoice = ChessPieceType::white_bishop;
            break;
        case 6:
            pieceChoice = ChessPieceType::white_rook;
            break;
        case 7:
            pieceChoice = ChessPieceType::white_queen;
            break;
    }
    Ref<ChessPieceModel2D> promotedPiece = createRef<ChessPieceModel2D>(pieceChoice);

    //change piece to selected piece
    int saveDir = 0;
    int promoPos = -1;
    if(tileY >= 4){
        promoPos = tileX + 56;
        m_children[promoPos]->getChildren().clear();
        m_children[promoPos]->addChild(promotedPiece);
        m_gameBoard.setBoardStateAt(tileX, 7, pieceChoice);
        saveDir -= 8;
    }else{
        promoPos = tileX;
        m_children[promoPos]->getChildren().clear();
        m_children[promoPos]->addChild(promotedPiece);
        m_gameBoard.setBoardStateAt(tileX, 0, pieceChoice);
        saveDir += 8;
    }

    //reset remaining covered pieces
    for(int i = 1; i < 4; i++){
        m_children[promoPos + saveDir * i]->getChildren().clear();
        if(saved[i-1])
            m_children[promoPos + saveDir * i]->addChild(saved[i-1]);    
        saved[i-1] = nullptr;
    }

    needsPromotionSelection = false;
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

void ChessBoardModel2D::setTileHightlight(int x, int
 y, bool b) {
    if( x < 0 || x > CHESS_COLS-1 || y < 0 || y > CHESS_ROWS-1)
        CORE_ASSERT(false, "Invalid tile coords!");

    Ref<ChessTileModel2D> tile = std::dynamic_pointer_cast<ChessTileModel2D>(m_children[y*CHESS_ROWS + x]);
    tile->setHighlight(b);
}