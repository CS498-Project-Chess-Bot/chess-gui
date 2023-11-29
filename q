[33mcommit 5ce26483a29245085d58abc64c8838ba769abf30[m[33m ([m[1;36mHEAD -> [m[1;32mswitchSides[m[33m, [m[1;31morigin/switchSides[m[33m)[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Nov 16 14:33:08 2023 -0500

    castling

[33mcommit 7760700257d8bc1cefb87d15b0ffef041f8e2c86[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Nov 15 16:17:22 2023 -0500

    add chess-engine repo

[33mcommit c1359e0c31d4354ef1228276f7b00f1deb21339d[m
Merge: a0fb38b 7baf9c2
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Nov 15 15:58:51 2023 -0500

    Merge branch 'switchSides' of https://github.com/CS498-Project-Chess-Bot/chess-gui into switchSides

[33mcommit a0fb38bf78f1434cc8e119c4f98dc3165b18b57b[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Nov 15 15:58:48 2023 -0500

    exec async bash commands for engine code

[33mcommit 7baf9c2eebc67c93ffe8b885a04156d2de993ff3[m
Author: Tacho2 <egbertcm23@gmail.com>
Date:   Wed Nov 15 03:33:39 2023 -0500

    Promotion Comments

[33mcommit b7c27adbc517246ba4ff2e1b5b5f639d643bd6c9[m
Author: Tacho2 <egbertcm23@gmail.com>
Date:   Wed Nov 15 03:23:56 2023 -0500

    En pessant and castle comments

[33mcommit c317634f82e8b7a28ae43e693e1a4269b27997b9[m
Author: Tacho2 <egbertcm23@gmail.com>
Date:   Wed Nov 15 02:47:26 2023 -0500

    Chess Logic 2.0

[33mcommit 07b717b321e1b6f2a46a4df7c71b93cab2028289[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Tue Nov 14 18:09:57 2023 -0500

    fix highlighting

[33mcommit 4507fc72dea293ffc6d45989ce1e491dd45327b5[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Tue Nov 14 15:20:35 2023 -0500

    can flip board, broke tile highlight

[33mcommit bc18e1ca48de6fcef07dfdf1815fb7b0b0f0d169[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Tue Nov 14 14:03:54 2023 -0500

    temp

[33mcommit 06bc48b39adf99426d72273acafa1e11ee575b28[m[33m ([m[1;32mdev[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Fri Nov 10 13:10:39 2023 -0500

    Clean up README

[33mcommit 5de9ee4a1b0fe217963095111ba140b89581a4e4[m
Merge: 893ac39 e083e7f
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Fri Nov 10 12:46:11 2023 -0500

    Merge pull request #23 from CS498-Project-Chess-Bot/boardMove
    
    Piece Movement
    Fix Board State logic

[33mcommit e083e7f2c9da8286adb21a1cf91562e8fb052f60[m
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 9 22:10:45 2023 -0500

    fix logic on pawns, rooks, bishops, and queen

[33mcommit 23119a68608e624ca6737646cac3c132a14ebe12[m
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 9 15:55:51 2023 -0500

    adjust indices for array

[33mcommit b84ecfaead20f7129c1116ccfdc0258912c8d6b9[m
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 9 13:43:31 2023 -0500

    redid pawn logic, add pawn to isPathBlocked, adjust rook logic, fix logic of isPathBlocked

[33mcommit 595ce89564d5f97f0a20365ec4368caeefd6af69[m
Merge: ab54af2 74eaced
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 9 12:22:27 2023 -0500

    Merge branch 'boardMove' of https://github.com/CS498-Project-Chess-Bot/chess-gui into boardMove

[33mcommit 74eaced6ebcb56b9e3a46f4c06c18d88776f9feb[m[33m ([m[1;31morigin/boardMove[m[33m, [m[1;32mboardMove[m[33m)[m
Author: Tacho2 <egbertcm23@gmail.com>
Date:   Wed Nov 8 23:01:25 2023 -0500

    Input Porcessing

[33mcommit ab54af2df2fcfa6b983131f72cacd726e91cdebf[m
Author: anna0021 <aeth245@uky.edu>
Date:   Wed Nov 8 20:39:01 2023 -0500

    queen logic added to isMoveValid

[33mcommit 893ac39c213339772f90a72fae22a336a863a6f0[m
Merge: 0e54598 82d28d0
Author: Tacho2 <62911430+Tacho2@users.noreply.github.com>
Date:   Wed Nov 8 13:13:52 2023 -0500

    Merge pull request #22 from CS498-Project-Chess-Bot/boardMove
    
    Board move

[33mcommit 82d28d0aaef424b4dc61a311545fc2f6cfa5cd8e[m
Author: anna0021 <aeth245@uky.edu>
Date:   Tue Nov 7 19:12:50 2023 -0500

    complete isPathBlocked, implement rook, king, bishop

[33mcommit 78c51237511c6e69adbabb09631777f310a05a0d[m
Author: anna0021 <aeth245@uky.edu>
Date:   Tue Nov 7 15:12:17 2023 -0500

    begin pathBlocked function

[33mcommit 0e54598e3e0f2bb67c262784b727a6d030e08150[m
Merge: 72b54c9 1870ba3
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Thu Nov 2 12:12:34 2023 -0400

    Merge pull request #21 from CS498-Project-Chess-Bot/boardMove
    
    Board Class

[33mcommit 1870ba377c04f0667dcad9d4fe9b4fd844e2a249[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Nov 2 12:09:48 2023 -0400

    knight and tile coord checking

[33mcommit ba67295381da36810555e5a56085cb2eafb9ce17[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Nov 2 12:02:44 2023 -0400

    add board class to FEN

[33mcommit 47afa71c5fd663207d51e4276ba96e9eedeae213[m
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 2 03:32:03 2023 -0400

    began knight implementation in isMoveValid

[33mcommit 8fa45abbafad093feaea67af1a31282cbadcc6c4[m
Author: anna0021 <aeth245@uky.edu>
Date:   Thu Nov 2 02:25:39 2023 -0400

    pawn implementation, move class adjustments, tuple implementation

[33mcommit dc0626c6f8e9d4bf9736ae3964868b972b2ecffc[m
Author: anna0021 <aeth245@uky.edu>
Date:   Wed Nov 1 16:54:54 2023 -0400

    update makeMove, add comments, restructing of move files

[33mcommit 2ed89115f411bbd665b5b517479bf65e7f9fa76f[m
Merge: 1f1fcb8 72b54c9
Author: anna0021 <aeth245@uky.edu>
Date:   Tue Oct 31 20:34:26 2023 -0400

    Merge branch 'dev' of https://github.com/CS498-Project-Chess-Bot/chess-gui into boardMove

[33mcommit 1f1fcb84391b4a2f3cf66acec4e09f4051393a85[m
Author: anna0021 <aeth245@uky.edu>
Date:   Tue Oct 31 20:32:25 2023 -0400

    initial commit

[33mcommit 72b54c9578fab60e92d41ff508a15d202e2301b5[m
Merge: 1b5ffb4 dba16ef
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Tue Oct 24 17:12:11 2023 -0400

    Merge pull request #20 from CS498-Project-Chess-Bot/UserInput
    
    User input

[33mcommit dba16ef9d9586b060c57fce21e7fd2c6d16380a5[m[33m ([m[1;31morigin/UserInput[m[33m, [m[1;32mUserInput[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Tue Oct 24 16:47:37 2023 -0400

    clickable tiles

[33mcommit 1b5ffb4946d3875cc2f10466a41796de7f7b485f[m
Merge: a1ab7a8 b282768
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Tue Oct 24 14:09:51 2023 -0400

    Merge pull request #19 from CS498-Project-Chess-Bot/AllChessTextures
    
    All chess textures

[33mcommit b282768af3f405f853641c99f536bb352021fa7f[m[33m ([m[1;31morigin/AllChessTextures[m[33m, [m[1;32mAllChessTextures[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Tue Oct 24 13:39:31 2023 -0400

    full board with all pieces, needed texture manager

[33mcommit a1ab7a8d13d962e2bb1eb678d6b40855640a3c16[m
Merge: ef17125 cc06a09
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Sun Oct 8 22:03:26 2023 -0400

    Merge pull request #16 from CS498-Project-Chess-Bot/ChessModels
    
    Chess Piece 2D models and Scene Rendering

[33mcommit cc06a09e145aa9c99be77310838c768951c77617[m[33m ([m[1;31morigin/ChessModels[m[33m, [m[1;32mChessModels[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Sun Oct 8 13:03:28 2023 -0400

    add tile models

[33mcommit c7835952ab20c236aae12f845806555e574ceb22[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Fri Oct 6 19:59:17 2023 -0400

    Refs, parenting, and delta time

[33mcommit 52b3fb0180d6ccd772d0784d4c2546fe0a7f4c88[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Oct 5 13:37:10 2023 -0400

    fix blending by sorting objects by z-value

[33mcommit 1d3fff80b4124554bf1d426a6f655111912d202e[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Oct 4 23:23:55 2023 -0400

    fix chess piece model render

[33mcommit a0dd4217e17a5407047f70b0da89450e3bd2cb20[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Oct 4 16:29:05 2023 -0400

    First chess piece object - BROKEN

[33mcommit 93fe2ff065b48359ff169c1e19d88c03d83d5510[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Oct 4 00:05:20 2023 -0400

    MVP matrices and camera class

[33mcommit ef17125d8fbacbaeb1ad3643e230be14360f883b[m
Merge: db8c6ee 713da04
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Tue Oct 3 18:14:15 2023 -0400

    Merge pull request #13 from CS498-Project-Chess-Bot/ShaderUniforms
    
    Shader Uniforms and Textured Primitives

[33mcommit 713da045d8c58d6ca9e975036e8894911966fbbf[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Tue Oct 3 13:23:22 2023 -0400

    add textures - pawn on screen

[33mcommit eccd5f15724cae36891511452551fc7062782ba2[m[33m ([m[1;31morigin/ShaderUniforms[m[33m, [m[1;32mShaderUniforms[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Mon Oct 2 22:35:25 2023 -0400

    Fix makefile to compile objects separate

[33mcommit c9e107336a0f9cbe99bc6389c276a89ea16a3ee7[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Mon Oct 2 17:20:50 2023 -0400

    add shader uniforms and glm

[33mcommit db8c6ee6c67018e0592b479aa9ce360cfc8313d1[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Sun Oct 1 23:48:34 2023 -0400

    barebones renderer

[33mcommit 5e5fc0b144a4743a7605e104ce190c7e91772f96[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Sun Oct 1 23:08:32 2023 -0400

    Vertex Arrays and variable buffer layouts

[33mcommit 8289f01ecd31db66fa701fe181321681fb0222d7[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Sun Oct 1 16:35:06 2023 -0400

    Basic Vertex Buffer class

[33mcommit 1dfaf947bf7b1a7bd3ed3bf77c8bc42f6b39547e[m
Merge: f425d49 13843bd
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Sun Sep 24 17:09:47 2023 -0400

    Merge branch 'main' into dev

[33mcommit f425d49d217e486fcb427dd6f6e1ea692d984cf6[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Sun Sep 24 16:59:26 2023 -0400

    quad drawn fixed shader bug

[33mcommit 393445f72de0760726d94c80a3972df47288a6e0[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Sat Sep 23 21:38:09 2023 -0400

    triangle (broken)

[33mcommit d4521ea0d721e75fa076948cc5f6ff831ede1018[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Sat Sep 23 20:21:09 2023 -0400

    Shaders

[33mcommit 6d565e08b4b2a161be009f03afb13469b4f59c78[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Sep 14 15:00:50 2023 -0400

    makefile options for macos platform

[33mcommit 13843bd2a04389de39f1ca8bd01309daf7cc5718[m
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Thu Sep 14 14:37:23 2023 -0400

    Dev #1 (#2)
    
    * GLFW and GLAD linking - Issues
    
    * fix gdi32 linking issues
    
    * basic app class
    
    ---------
    
    Co-authored-by: Matthew Whalen <whalenm20@uky.edu>

[33mcommit 3d5d257448a8405af792455021190ad1aa75c0a4[m
Merge: 87d11c6 c5fdb86
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Thu Sep 14 14:36:14 2023 -0400

    Merge pull request #1 from CS498-Project-Chess-Bot/GLFW-GLAD
    
    basic app class

[33mcommit c5fdb86a59f3a7998277fb4d9bf5b79a424f15e4[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Sep 14 14:35:22 2023 -0400

    basic app class

[33mcommit 87d11c6206a0db20b9cc0324fc3101b8bc75b76c[m
Author: Matthew Whalen <whalenm20@uky.edu>
Date:   Thu Sep 14 14:03:47 2023 -0400

    fix gdi32 linking issues

[33mcommit 347171ba79598af16f7bc46982556c8690e9a07c[m[33m ([m[1;31morigin/GLFW-GLAD[m[33m)[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Sep 13 19:11:50 2023 -0400

    GLFW and GLAD linking - Issues

[33mcommit b46ca47dc9d784b0f75de2ae37b24aae62ee575f[m
Author: Matthew Whalen <mrwhalen22@gmail.com>
Date:   Wed Sep 13 18:00:17 2023 -0400

    add makefile

[33mcommit 97166a1e3ecc86ef1cd4e3a25876d4ea6b0a6fd7[m
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Wed Sep 13 17:17:16 2023 -0400

    Create README.md

[33mcommit ddb4175293c41b34be68fe96a6b58aa355579475[m
Author: Matthew Whalen <79370038+mrwhalen22@users.noreply.github.com>
Date:   Tue Sep 5 15:02:52 2023 -0400

    Initial commit
