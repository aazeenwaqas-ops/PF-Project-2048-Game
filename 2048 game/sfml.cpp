
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
extern int board[4][4];
extern int score;
void setupgame();
bool moveleft();
bool moveright();
bool moveup();
bool movedown();
void generatetile();

sf::Color getTileColor(int value) { // selecting tile colours
    if (value == 0) {
        return sf::Color(72, 101, 129);
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
    else {
        return sf::Color(217, 240, 255);
    }
}
int main() {
    sf::RenderWindow window(sf::VideoMode({ 520, 650 }), "2048");
    sf::Color background(16, 42, 67);
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        cout << "Font could not be loaded!" << endl;
        return -1;
    }
    // title
    sf::Text title(font, "2048", 45);
    title.setFillColor(sf::Color(217, 240, 255));
    title.setPosition({ 190.f, 35.f });
    // start screen
    bool gameStarted = false;
    sf::Text instructions(font, "Combine tiles to reach 2048!", 20);
    instructions.setFillColor(sf::Color(217, 240, 255));
    instructions.setPosition({ 115.f, 300.f });
    sf::RectangleShape playButton({ 180.f, 60.f });
    playButton.setPosition({ 170.f, 400.f });
    playButton.setFillColor(sf::Color(35, 137, 201));
    sf::Text playText(font, "PLAY", 25);
    playText.setFillColor(sf::Color::White);
    playText.setPosition({ 230.f, 415.f });
    // grid
    int startX = 40, startY = 150, tileSize = 100, gap = 10;
    sf::RectangleShape gameBoard({ 450.f, 450.f });
    gameBoard.setPosition({ (float)startX, (float)startY });
    gameBoard.setFillColor(sf::Color(36, 59, 83));
    sf::RectangleShape tile({ 100.f, 100.f });
    sf::Text scoreText(font, "Score: 0", 25);
    scoreText.setFillColor(sf::Color(217, 240, 255));
    scoreText.setPosition({ 190.f, 95.f });
    while (window.isOpen())
    { // game loop
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (!gameStarted) {
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left) {
                        int mouseX = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
                        int mouseY = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
                        if (mouseX >= 170 && mouseX <= 350 && mouseY >= 400 && mouseY <= 460) {
                            setupgame();
                            gameStarted = true;
                        }
                    }
                }
            }
            // controls
            else {
                if (event->is<sf::Event::KeyPressed>()) {
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Left) {
                        if (moveleft()) {
                            generatetile();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Right) {
                        if (moveright()) {
                            generatetile();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Up) {
                        if (moveup()) {
                            generatetile();
                        }
                    }
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Down) {
                        if (movedown()) {
                            generatetile();
                        }
                    }
                }
            }
        }
        window.clear(background);
        if (!gameStarted) {
            window.draw(title);
            window.draw(instructions);
            window.draw(playButton);
            window.draw(playText);
        }
        else {
            scoreText.setString("Score: " + to_string(score));
            window.draw(title);
            window.draw(scoreText);
            window.draw(gameBoard);
            // drawing tiles
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    int x = startX + gap + col * (tileSize + gap);
                    int y = startY + gap + row * (tileSize + gap);
                    tile.setPosition({
                        (float)x,
                        (float)y
                        });
                    tile.setFillColor(getTileColor(board[row][col]));
                    window.draw(tile);
                    int value = board[row][col];
                    if (value != 0) {
                        sf::Text tileText(font, to_string(value), 30);
                        tileText.setFillColor(sf::Color(16, 42, 67));
                        sf::FloatRect bounds = tileText.getLocalBounds();
                        tileText.setOrigin({ bounds.position.x + bounds.size.x / 2.f,bounds.position.y + bounds.size.y / 2.f });
                        tileText.setPosition({ x + tileSize / 2.f,y + tileSize / 2.f });
                        window.draw(tileText);
                    }
                }
            }
        }
        window.display();
    }
    return 0;
}
