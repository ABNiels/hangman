mod word_gen;
use word_gen::word_gen::gen_word;

mod game;
use game::game::play_game;

fn main() {
    let word: String = gen_word();

    play_game(word);
}
