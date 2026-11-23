#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
extern int board[4][4];
extern int score;
extern int bestscore;
void setupgame();
bool moveleft();
bool moveright();
bool moveup();
bool movedown();
void generatetile();
bool checkwin();
bool checkgameover();
void loadbestscore();
void savebestscore();
sf::Color getTileColor(int value) {
    if (value == 0) {
        return sf::Color(39, 57, 77);
    }
    else if (value == 2) {
        return sf::Color(130, 154, 177);
    }
    else if (value == 4) {
        return sf::Color(98, 182, 232);
    }
    else if (value == 8) {
        return sf::Color(35, 137, 201);
    }
    else if (value == 16) {
        return sf::Color(20, 93, 160);
    }
    else if (value == 32) {
        return sf::Color(15, 75, 135);
    }
    else if (value == 64) {
        return sf::Color(10, 55, 105);
    }
    else if (value == 128) {
        return sf::Color(80, 160, 210);
    }
    else if (value == 256) {
        return sf::Color(55, 130, 190);
    }
    else if (value == 512) {
        return sf::Color(35, 105, 170);
    }
    else if (value == 1024) {
        return sf::Color(20, 80, 145);
    }
    else if (value == 2048) {
        return sf::Color(217, 240, 255);
    }
    else {
        return sf::Color(180, 210, 235);
    }
}
void centerText(sf::Text& text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
    text.setPosition({ x, y });
}
int main() {
    loadbestscore();
    sf::RenderWindow window(sf::VideoMode({ 520, 680 }), "2048");
    sf::Color background(12, 24, 40);
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        cout << "Font could not be loaded" << endl;
        return -1;
    }
    // gameplay title
    sf::Text title(font, "2048", 48);
    title.setFillColor(sf::Color(217, 240, 255));
    title.setPosition({ 35.f, 25.f });
    // start screen
    bool gameStarted = false;
    bool gamewon = false;
    bool gameover = false;
    bool continued = false;
    sf::Text startTitle(font, "2048", 85);
    startTitle.setFillColor(sf::Color(217, 240, 255));
    centerText(startTitle, 260.f, 170.f);
    sf::Text startSubtitle(font, "THE NUMBER PUZZLE", 18);
    startSubtitle.setFillColor(sf::Color(98, 182, 232));
    centerText(startSubtitle, 260.f, 245.f);
    sf::Text startInstructions(font, "Combine the tiles and reach 2048!", 19);
    startInstructions.setFillColor(sf::Color(180, 210, 235));
    centerText(startInstructions, 260.f, 435.f);
    sf::Text startHint(font, "USE YOUR ARROW KEYS TO PLAY", 13);
    startHint.setFillColor(sf::Color(110, 145, 175));
    centerText(startHint, 260.f, 600.f);
    // decorative tiles on start screen
    int decorativeValues[4] = { 2, 4, 8, 16 };
    sf::RectangleShape decorativeTile({ 70.f, 70.f });
    for (int i = 0; i < 4; i++) {
        decorativeTile.setPosition({ 95.f + i * 80.f, 315.f });
        decorativeTile.setFillColor(getTileColor(decorativeValues[i]));
    }
    sf::RectangleShape playButton({ 200.f, 65.f });
    playButton.setPosition({ 160.f, 490.f });
    playButton.setFillColor(sf::Color(35, 137, 201));
    playButton.setOutlineThickness(2.f);
    playButton.setOutlineColor(sf::Color(98, 182, 232));
    sf::Text playText(font, "PLAY GAME", 22);
    playText.setFillColor(sf::Color::White);
    centerText(playText, 260.f, 522.5f);
    // result screen
    sf::RectangleShape resultPanel({ 400.f, 300.f });
    resultPanel.setPosition({ 60.f, 205.f });
    resultPanel.setFillColor(sf::Color(23, 40, 59));
    resultPanel.setOutlineThickness(2.f);
    resultPanel.setOutlineColor(sf::Color(55, 105, 145));
    sf::Text resultText(font, "", 42);
    resultText.setFillColor(sf::Color(217, 240, 255));
    sf::Text resultSubtitle(font, "", 18);
    resultSubtitle.setFillColor(sf::Color(145, 180, 210));
    sf::Text finalScoreText(font, "", 20);
    finalScoreText.setFillColor(sf::Color(98, 182, 232));
    sf::RectangleShape restartButton({ 200.f, 55.f });
    restartButton.setPosition({ 160.f, 425.f });
    restartButton.setFillColor(sf::Color(35, 137, 201));
    sf::Text restartText(font, "PLAY AGAIN", 20);
    restartText.setFillColor(sf::Color::White);
    centerText(restartText, 260.f, 452.5f);
    sf::RectangleShape continueButton({ 200.f, 55.f });
    continueButton.setPosition({ 160.f, 495.f });
    continueButton.setFillColor(sf::Color(28, 85, 125));
    sf::Text continueText(font, "CONTINUE", 20);
    continueText.setFillColor(sf::Color::White);
    centerText(continueText, 260.f, 522.5f);
    // grid
    int startX = 35, startY = 190, tileSize = 100, gap = 10;
    sf::RectangleShape gameBoard({ 450.f, 450.f });
    gameBoard.setPosition({ (float)startX, (float)startY });
    gameBoard.setFillColor(sf::Color(23, 40, 59));
    sf::RectangleShape tile({ 100.f, 100.f });
    // score boxes
    sf::RectangleShape scoreBox({ 205.f, 55.f });
    scoreBox.setPosition({ 35.f, 85.f });
    scoreBox.setFillColor(sf::Color(28, 48, 69));
    sf::RectangleShape bestScoreBox({ 205.f, 55.f });
    bestScoreBox.setPosition({ 280.f, 85.f });
    bestScoreBox.setFillColor(sf::Color(28, 48, 69));
    sf::Text scoreText(font, "SCORE\n0", 18);
    scoreText.setFillColor(sf::Color(217, 240, 255));
    sf::Text bestScoreText(font, "BEST SCORE\n0", 18);
    bestScoreText.setFillColor(sf::Color(217, 240, 255));
    // keyboard instructions
    sf::Text controlsHint(font, "USE ARROW KEYS TO MOVE", 13);
    controlsHint.setFillColor(sf::Color(145, 170, 195));
    controlsHint.setPosition({ 35.f, 155.f });
    // new game button
    sf::RectangleShape newGameButton({ 130.f, 35.f });
    newGameButton.setPosition({ 355.f, 150.f });
    newGameButton.setFillColor(sf::Color(35, 137, 201));
    sf::Text newGameText(font, "NEW GAME", 15);
    newGameText.setFillColor(sf::Color::White);
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (!gameStarted) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                        int mouseX = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
                        int mouseY = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
                        if (mouseX >= 160 && mouseX <= 360 && mouseY >= 490 && mouseY <= 555) {
                            setupgame();
                            gameStarted = true;
                            gamewon = false;
                            gameover = false;
                        }
                    }
                }
            }
            else if (gamewon || gameover) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                        int mouseX = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
                        int mouseY = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
                        if (mouseX >= 160 && mouseX <= 360 && mouseY >= 425 && mouseY <= 480) {
                            setupgame();
                            gamewon = false;
                            gameover = false;
                            continued = false;
                        }
                        else if (gamewon && mouseX >= 160 && mouseX <= 360 && mouseY >= 495 && mouseY <= 550) {
                            gamewon = false;
                            continued = true;
                        }
                    }
                }
            }
            // controls
            else if (!gamewon && !gameover) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                        int mouseX = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
                        int mouseY = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
                        if (mouseX >= 355 && mouseX <= 485 && mouseY >= 150 && mouseY <= 185) {
                            setupgame();
                            gamewon = false;
                            gameover = false;
                            continued = false;
                        }
                    }
                }
                if (event->is<sf::Event::KeyPressed>()) {
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
                        if (moveleft()) {
                            generatetile();
                            savebestscore();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
                        if (moveright()) {
                            generatetile();
                            savebestscore();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
                        if (moveup()) {
                            generatetile();
                            savebestscore();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
                        if (movedown()) {
                            generatetile();
                            savebestscore();
                        }
                    }
                    if (checkwin() && !continued) {
                        gamewon = true;
                    }
                    else if (checkgameover()) {
                        gameover = true;
                    }
                }
            }
        }
        window.clear(background);
        if (!gameStarted) {
            window.draw(startTitle);
            window.draw(startSubtitle);
            for (int i = 0; i < 4; i++) {
                decorativeTile.setPosition({ 95.f + i * 80.f, 315.f });
                window.draw(decorativeTile);
                sf::Text decorativeText(font, to_string(decorativeValues[i]), 25);
                decorativeText.setFillColor(sf::Color(16, 42, 67));
                centerText(decorativeText, 130.f + i * 80.f, 350.f);
                window.draw(decorativeText);
            }
            window.draw(startInstructions);
            window.draw(playButton);
            window.draw(playText);
            window.draw(startHint);
        }
        else if (gamewon || gameover) {
            if (gamewon) {
                resultText.setString("YOU WON!");
                resultSubtitle.setString("Amazing! You reached 2048.");
            }
            else {
                resultText.setString("GAME OVER!");
                resultSubtitle.setString("No more moves are available.");
            }
            finalScoreText.setString("YOUR SCORE: " + to_string(score));
            centerText(resultText, 260.f, 295.f);
            centerText(resultSubtitle, 260.f, 355.f);
            centerText(finalScoreText, 260.f, 395.f);
            window.draw(title);
            window.draw(resultPanel);
            window.draw(resultText);
            window.draw(resultSubtitle);
            window.draw(finalScoreText);
            window.draw(restartButton);
            window.draw(restartText);
            if (gamewon) {
                window.draw(continueButton);
                window.draw(continueText);
            }
        }
        else {
            scoreText.setString("SCORE\n" + to_string(score));
            bestScoreText.setString("BEST SCORE\n" + to_string(bestscore));
            // centering score text
            sf::FloatRect scoreBounds = scoreText.getLocalBounds();
            scoreText.setOrigin({ scoreBounds.position.x + scoreBounds.size.x / 2.f, scoreBounds.position.y + scoreBounds.size.y / 2.f });
            scoreText.setPosition({ 137.5f, 112.5f });
            // centering best score text
            sf::FloatRect bestBounds = bestScoreText.getLocalBounds();
            bestScoreText.setOrigin({ bestBounds.position.x + bestBounds.size.x / 2.f, bestBounds.position.y + bestBounds.size.y / 2.f });
            bestScoreText.setPosition({ 382.5f, 112.5f });
            // centering new game text
            sf::FloatRect newGameBounds = newGameText.getLocalBounds();
            newGameText.setOrigin({ newGameBounds.position.x + newGameBounds.size.x / 2.f, newGameBounds.position.y + newGameBounds.size.y / 2.f });
            newGameText.setPosition({ 420.f, 167.5f });
            window.draw(title);
            window.draw(scoreBox);
            window.draw(bestScoreBox);
            window.draw(scoreText);
            window.draw(bestScoreText);
            window.draw(controlsHint);
            window.draw(newGameButton);
            window.draw(newGameText);
            window.draw(gameBoard);
            // drawing tiles
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    int x = startX + gap + col * (tileSize + gap);
                    int y = startY + gap + row * (tileSize + gap);
                    tile.setPosition({ (float)x, (float)y });
                    tile.setFillColor(getTileColor(board[row][col]));
                    window.draw(tile);
                    int value = board[row][col];
                    if (value != 0) {
                        sf::Text tileText(font, to_string(value), 30);
                        if (value >= 8 && value <= 1024) {
                            tileText.setFillColor(sf::Color::White);
                        }
                        else {
                            tileText.setFillColor(sf::Color(16, 42, 67));
                        }
                        sf::FloatRect bounds = tileText.getLocalBounds();
                        tileText.setOrigin({ bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f });
                        tileText.setPosition({ x + tileSize / 2.f, y + tileSize / 2.f });
                        window.draw(tileText);
                    }
                }
            }
        }
        window.display();
    }
    return 0;
}
