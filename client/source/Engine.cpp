
#include "Engine.h"
#define RESOLUTION_WIDTH 800.0
#define RESOLUTION_HEIGHT 900.0

const sf::Time Engine::TimePerFrame = seconds(1.f/60.f);

Engine::Engine() : grid(window), client(), lobby(window), mousePos(grid),  mainMenu(window), player(grid, mousePos), game(player),
                   waitingRoom(window){
    // Init window
    resolution = Vector2f(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    window.create(VideoMode(
            resolution.x, resolution.y),
                  "Scrabble-BR", Style::Default);
    window.setFramerateLimit(FPS);

    // Init view
    view.setSize(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
    view.setCenter(window.getSize().x / 2.0, window.getSize().y / 2.f);
    client.initialize();
    player.sock = client.sock;
    flag = false;
    startFlag = false;
    endFlag = false;
}

Engine::~Engine() = default;

void Engine::draw() {
    if(!startFlag) {
        for(int i = 0; i < 15; i++) {
            for(int j = 0; j < 15; j++) {
                player.gameState[i][j] = '0';
            }
        }
        clock.restart();
        write(client.sock, "!", 1);
        read(client.sock, client.buffer, 2);
        int pos = client.buffer[0] - '0';
        char letter = client.buffer[1];
        Vector2f coords = player.startingPositions[pos];
        player.startingPosition = pos;
        player.gameState[coords.x][coords.y] = letter;
        player.currentWordCoordinates = coords;
        player.playerPositions.push_back(coords);
        mousePos.lockedTilePos = coords;
        startFlag = true;
    }
    if(!player.isAlive && !endFlag) {
        write(client.sock, "{", 1);
        read(client.sock, client.buffer, 1);
        player.possiblePlace = client.buffer[0] - '0';
        endFlag = true;
    }
    if(!player.isAlive) {
        Event event;
        while(window.pollEvent(event)) {
            // Window closed
            if (event.type == Event::Closed) {
                window.close();
            }
            // Handle Keyboard input
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Return) {
                    flag = false;
                    lobby.flag = false;
                    endFlag = false;
                    startFlag = false;
                    clock.restart();
                    player.clear();
                    grid.clear();
                    mousePos.clear();
                    game.clear();
                    window.clear();
                    break;
                }
            }
        }
    }
    write(client.sock, "&", 1);
    read(client.sock, client.buffer, 225);
    int cnt = 0;
    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
            if(!player.isAlive && ((i == 0 && j == 0) || (i == 0 && j == 14) || (i == 14 && j == 0) || (i == 14 && j == 14))) {
                cnt++;
                continue;
            }
            if(client.buffer[cnt] != '0') {
                player.gameState[i][j] = client.buffer[cnt];
            }
            cnt++;
        }
    }
    // Update delta time
    dt = dtClock.restart().asSeconds();
    if(clock.getElapsedTime().asSeconds() >= 30.f) {
        clock.restart();
        grid.refreshGrid(game.getShrinkage());
        game.shrinkGrid();
        mousePos.setDangerZones(game.getDangerZones());
    }
    game.checkIfPlayerKilled();
    // Render window
    // window.clear(Color::Black);
    window.setView(view);


    // Update mouse position
    mousePos.updateMousePos(window);
    mousePos.handleMouseClick(window, player.getGameState(), player.playerPositions);
    mousePos.handleArrowKeys();
    window.setView(window.getDefaultView());


    // Render game elements
    grid.draw_grid(window);
    mousePos.updateTileSelector(window);
    mousePos.checkArrowPos();
    mousePos.drawArrow(window);


    player.drawLetters(window);
    player.gameStateToGrid(window);
    player.playerInput(window);
    if(!player.getAliveFlag()){
        player.playerDead(window);
    }
    // Render UI
    window.display();
}

void Engine::run() {

    mousePos.initTileSelector(window);
    while(window.isOpen()){

        if(!mainMenu.getPlayFlag() &&
        !mainMenu.getOptionsFlag() &&
        !mainMenu.getAboutFlag()) {
            window.clear();
            input();
            continue;
        }
        if(mainMenu.getPlayFlag() && !lobby.isEnterRoomFlag()){
            mousePos.initTileSelector(window);
            window.clear();
            if(flag) {
                draw();
            }
            flag = lobby.draw(client);
        }


        //window.clear();
//        input();
        //draw();
    }
}

void Engine::input() {
    Event event{};

    while(window.pollEvent(event)){
        // Window closed
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == 8) { // 8 is the ASCII value for backspace
                if (!playerInput.empty()) {
                    playerInput.pop_back();
                }
            } else if(event.text.unicode >= 96 && event.text.unicode <= 122 && playerInput.length() < 16) {
                playerInput += event.text.unicode;
            }
            mainMenu.setPlayerText(playerInput);
            mainMenu.setNickname();
        }
        // Handle Keyboard input
        if(event.type == Event::KeyReleased){

            if (event.key.code == Keyboard::Up){
                mainMenu.moveUp();
                break;
            }
            if (event.key.code == Keyboard::Down){
                mainMenu.moveDown();
                break;
            }
            if (event.key.code == Keyboard::Return){
                int x = mainMenu.mainMenuPressed();
                if(x == 2 && playerInput.length() > 0){

                    if(client.validateNickAvailability(playerInput) == '1') {
                        player.setNickname(playerInput);
                        mainMenu.setPlayFlag(true);
                    }
                    else {
                        playerInput = "";
                        mainMenu.setPlayerText(playerInput);
                        mainMenu.setNickname();
                    }
//                    if(lobby.validateNickAvailability(playerInput)) {
//                        player.setNickname(playerInput);
//                        mainMenu.setPlayFlag(true);
//                    }
//                    else {
//                        playerInput = "";
//                        mainMenu.setPlayerText(playerInput);
//                        mainMenu.setNickname();
//                    }

                }
                if(x == 3){
                    window.close();
                    break;
                }
            }
        }
    }
    window.clear();
    mainMenu.draw();
    window.display();
}





