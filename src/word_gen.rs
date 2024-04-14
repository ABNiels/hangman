pub mod word_gen {
    use std::fs::File;
    use std::io::{BufRead, BufReader, };
    use rand::Rng;

    pub fn gen_word() -> String {
        // Perform some operations here
        println!("Generating word...");
        let f = File::open("words.txt").expect("Unable to open file\n");

        let reader: BufReader<File> = BufReader::new(f);
        let line_count: usize = reader.lines().count();
        let word_index: usize = rand::thread_rng().gen_range(0..line_count);

        // reopen file because I can't for the life of me figure out how to seek the start
        let f = File::open("words.txt").expect("Unable to open file\n");
        let reader = BufReader::new(f);

        reader.lines().nth(word_index).unwrap().unwrap()
    }
}