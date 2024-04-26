pub mod game {
    use std::io;
    struct GameState {
        guesses_printable: String,
        word: String,
        word_printable: String
    }

    impl GameState {
        pub fn new(word: String) -> GameState {
            // Default no guesses, display is all underscores
            let underscores: String = word.chars().map(|_| '_').collect();
            GameState {
                guesses_printable: String::from(""),
                word: word,
                word_printable: underscores
            }
        }

        pub fn check_win (&self) -> i8 {
            ((self.word == self.word_printable) as i8) - ((self.guesses_printable.len() == 50) as i8)
        }

        pub fn parse_input (&mut self, input: char) -> () {
            // range check
            if input as u8 >= 'a' as u8 && input as u8 <= 'z' as u8 && !self.guesses_printable.contains(input) {
                // update printable guesses
                self.guesses_printable += &input.to_string();
                self.guesses_printable += " ";

                // update printable word
                for (i, letter) in self.word.chars().enumerate() {
                    if letter == input {
                        self.word_printable.replace_range(i..i+1, &input.to_string());
                    }
                }
            }
        }

        pub fn print_game (&mut self) -> () {
            println!("Guessed letters: {}", self.guesses_printable);
            println!("Word: {}", self.word_printable);
        }
    }

    fn get_input() -> char {
        let mut user_input: String = String::new();

        print!("Guess a letter: ");
        io::stdin().read_line(&mut user_input).expect("Failed to read line");
        user_input.chars().next().unwrap() //first char only
    }

    pub fn play_game(word: String) -> () {
        let mut gamestate: GameState = GameState::new(word);
        let mut character: char;

        gamestate.print_game();
        while gamestate.check_win() == 0 {
            character = get_input();
            gamestate.parse_input(character);
            gamestate.print_game();
        }

        if gamestate.check_win() == -1 {
            println!("You lose!");
        }
        else {
            println!("You win!");
        }

    }
}