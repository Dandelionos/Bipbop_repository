#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// this function checks if 2 sprites are colliding
bool Collision(const Sprite& a, const Sprite& b)
{
    return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

// this function checks if the ball collides with the bottom part of a square
bool BottomCollision(const Sprite& a, const Sprite& b)
{
    if((a.getPosition().x+10>=b.getPosition().x)&&(a.getPosition().x+10<=b.getPosition().x+40))
        if(a.getPosition().y==b.getPosition().y+40)
            return true;
    return false;

}

// this function checks if the ball collides with the top part of a square
bool TopCollision(const Sprite& a, const Sprite& b)
{
    if((a.getPosition().x+10>=b.getPosition().x)&&(a.getPosition().x+10<=b.getPosition().x+40))
        if(a.getPosition().y+20==b.getPosition().y)
            return true;
    return false;

}

// this function checks if the ball collides with the left part of a square
bool LeftCollision(const Sprite& a, const Sprite& b)
{
    if((a.getPosition().y+10>b.getPosition().y)&&(a.getPosition().y+10<b.getPosition().y+40))
        if(a.getPosition().x+20==b.getPosition().x)
            return true;
    return false;

}

// this function checks if the ball collides with the right part of a square
bool RightCollision(const Sprite& a, const Sprite& b)
{
    if((a.getPosition().y+10>b.getPosition().y)&&(a.getPosition().y+10<b.getPosition().y+40))
        if(a.getPosition().x==b.getPosition().x+40)
            return true;
    return false;
}



int main()
{

    // creates a window with the required dimensions and the title and framerate
    RenderWindow window(VideoMode(640, 480), "Bip-bop");
    window.setFramerateLimit(60);

    // loads and creates the font that will be used by the text
    Font my_font;
    my_font.loadFromFile(".././arial.ttf");

    // loads the textures for the ball, board and squares
    Texture ball_texture, board_texture, square_texture;
    ball_texture.loadFromFile(".././ball.png");
    board_texture.loadFromFile(".././board.png");
    square_texture.loadFromFile(".././square.png");

    // creates the ball, board and squares classes
    Sprite ball(ball_texture), board(board_texture), squares[30];

    // creates the clock class responsible for measuring the time
    Clock clock;

    // creates the text files that will appear on the window
    Text lives_txt, clock_txt, integrity_txt[30], score_txt, game_over_txt, game_win_txt;

    // crates variables
    int lives_squares[30], score = 0, max_score = 0;

    // creates the text for the lives
    lives_txt.setFont(my_font);
    lives_txt.setString("Lives: 3");
    lives_txt.setPosition(20, 150);
    lives_txt.setFillColor(Color::White);

    // creates the text for the score
    score_txt.setFont(my_font);
    score_txt.setString("Score: 0");
    score_txt.setPosition(20, 250);
    score_txt.setFillColor(Color::White);

    // sets the positions of the board and ball
    board.setPosition(260, 460);
    ball.setPosition(310, 240);



    // the following while creates the squares, sets their position, sets their lives in the frequency vector and creates the max score
    int i = 0;
    float j = 30.0, k = 165.0;
    while (i < 21)
    {
        if (i < 13)
        {
            squares[i].setTexture(square_texture);
            squares[i].setPosition(Vector2f(j, 5.f));
            lives_squares[i] = 1;
            max_score = max_score + lives_squares[i] * 10;
            j += 45;
        }
        if (i > 12 && i < 20)
        {
            squares[i].setTexture(square_texture);
            squares[i].setPosition(Vector2f(k, 50.f));
            lives_squares[i] = 2;
            max_score = max_score + lives_squares[i] * 10;
            k += 45;
        }
        if (i == 20)
        {
            squares[i].setTexture(square_texture);
            squares[i].setPosition(Vector2f(300.f, 95.f));
            lives_squares[i] = 3;
            max_score = max_score + lives_squares[i] * 10;
        }

        i++;
    }


    // the following while creates the integrity score texts, sets their position and color, and the number they are supposed to represent
    int p = 0;
    float h = 30.0, g = 165.0;
    while (p < 21)
    {
        if (p < 13)
        {
            integrity_txt[p].setFont(my_font);
            integrity_txt[p].setFillColor(Color::White);
            integrity_txt[p].setString("1");
            integrity_txt[p].setPosition(Vector2f(h, 5.f));
            h += 45;
        }
        if (p > 12 && p < 20)
        {
            integrity_txt[p].setFont(my_font);
            integrity_txt[p].setFillColor(Color::White);
            integrity_txt[p].setString("2");
            integrity_txt[p].setPosition(Vector2f(g, 50.f));
            g += 45;
        }
        if (p == 20)
        {
            integrity_txt[p].setFont(my_font);
            integrity_txt[p].setFillColor(Color::White);
            integrity_txt[p].setString("3");
            integrity_txt[p].setPosition(Vector2f(300.f, 95.f));
        }

        p++;
    }


    // creates the velocities for the ball
    float xVelocity = -5;
    float yVelocity = -5;


    int lives_lost_ball = 0, game_over = 0;


    // creates the loop that keeps updating the game
    while (window.isOpen())
    {
        // creates an event
        Event E;


        // in the while: the window closes if the escape button is pressed and the board movement is implemented using A and D keys
        while (window.pollEvent(E))
        {
            if (E.type == Event::Closed)
                window.close();
            if (E.type == Event::KeyPressed && E.key.code == Keyboard::Escape)
                window.close();
            Vector2f board_pos = board.getPosition();
            if (E.type == Event::KeyPressed && E.key.code == Keyboard::A && board_pos.x != 0)
                board.move(-20, 0);
            if (E.type == Event::KeyPressed && E.key.code == Keyboard::D && board_pos.x + 120 != 640)
                board.move(+20, 0);
        }



        // clears the previous frame and makes the window background black
        window.clear(Color::Black);

        // takes the time from the clock class
        Time time_played = clock.getElapsedTime();

        // checks if you reached the max score and won the game and puts a "you won" text on the screen
        if (max_score == score)
        {
            game_over = 1;
            game_win_txt.setFont(my_font);
            game_win_txt.setString("You won! Congrats!");
            game_win_txt.setPosition(200, 220);
            game_win_txt.setFillColor(Color::Green);

        }

        // checks if you lost the game and creates the in game time in seconds
        if (game_over == 0)
        {
            clock_txt.setFont(my_font);
            clock_txt.setString("Time: " + to_string(int(time_played.asSeconds())));
            clock_txt.setPosition(20, 200);
            clock_txt.setFillColor(Color::White);
        }

        // takes the coordinates of the ball and the board
        Vector2f ball_pos = ball.getPosition();
        Vector2f board_pos = board.getPosition();


        // makes the center x coordinates for the ball and board
        float ball_pos_center_x= ball_pos.x+10;
        float board_pos_center_x= board_pos.x+60;

        // activates the brute-force AI, 0 for the player to control the board
        int AI=1;

        // makes the board follow the ball if the ball is to the right
        if(ball_pos_center_x > board_pos_center_x && AI==1)
        {

            if(board_pos_center_x+ 60 <640)
                board.move(10, 0);

        }

        // makes the board follow the ball if the ball is to the left
        if( ball_pos_center_x < board_pos_center_x && AI==1)
        {
            if(board_pos_center_x-60 >0)
                board.move(-10, 0);
        }



        // the 2 ifs make the boundaries of the window for the left, right and top parts
        if (ball_pos.x < 1 || ball_pos.x > 620) {
            xVelocity = xVelocity * -1;
        }
        if (ball_pos.y < 1) {
            yVelocity = yVelocity * -1;
        }


        // the collision detection between the ball and the squares and movement change for the ball
        ball.move(xVelocity, yVelocity);
        for (int c = 0; c < 21; c++)
        {
            if(BottomCollision(ball, squares[c]) || TopCollision(ball, squares[c]))
                yVelocity=-yVelocity;

            else if(LeftCollision(ball, squares[c]) || RightCollision(ball, squares[c]))
                xVelocity=-xVelocity;

        }


        // changes the score and the integrity of the squares; also removes squares and integrity text from the window
        for (int c = 0; c < 21; c++) {
            if ((TopCollision(ball, squares[c]) == 1) || (BottomCollision(ball, squares[c]) == 1) ||(LeftCollision(ball, squares[c]) == 1) || (RightCollision(ball, squares[c]) == 1))
            {
                score += 10;
                score_txt.setString("Score: " + to_string(score));

                if (lives_squares[c] > 1)
                {
                    lives_squares[c]--;
                    integrity_txt[c].setString(to_string(lives_squares[c]));


                }
                else
                {
                    squares[c].setPosition(0, -100);
                    integrity_txt[c].setPosition(0, -100);
                }


            }
        }



        // the collision detection between the ball and the board and movement change for the ball
        if (Collision(board, ball) == 1)
        {
            yVelocity = yVelocity * -1;
        }


        // the 3 ifs change the lives text, restart the ball position, and create the game over text
        if (ball_pos.y > 470 && lives_lost_ball == 2 && game_over == 0)
        {
            game_over_txt.setFont(my_font);
            game_over_txt.setString("Game over!");
            game_over_txt.setPosition(230, 220);
            game_over_txt.setFillColor(Color::Red);
            lives_txt.setString("Lives: 0");
            game_over = 1;

        }
        if (ball_pos.y > 470 && lives_lost_ball == 1)
        {
            lives_txt.setString("Lives: 1");
            lives_lost_ball++;
            ball.setPosition(310, 240);
            yVelocity = yVelocity * -1;

        }
        if (ball_pos.y > 470 && lives_lost_ball == 0)
        {
            lives_txt.setString("Lives: 2");
            lives_lost_ball++;
            ball.setPosition(310, 240);
            yVelocity = yVelocity * -1;

        }


        // draws the board and ball on the window
        window.draw(board);
        window.draw(ball);

        // draws the squares on the window
        for (int x = 0; x < 21; x++)
        {
            window.draw(squares[x]);
        }

        // draws all the texts on the window
        window.draw(lives_txt);
        window.draw(clock_txt);
        window.draw(score_txt);
        window.draw(game_over_txt);
        window.draw(game_win_txt);

        for (int f = 0; f < 21; f++)
        {
            window.draw(integrity_txt[f]);
        }


        // displays the window on the screen
        window.display();
    }

    return 0;
}