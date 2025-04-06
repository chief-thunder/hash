use rand::Rng;
use rand::SeedableRng;
use rand::distributions::Alphanumeric;
use rand::prng::chacha::ChaChaRng;
use std::iter;

fn main() {
    let mut rng = ChaChaRng::from_entropy(); // Initialize ChaChaRng with a random seed
    let mut password;

    loop {
        // Generate a random password of length 10
        password = iter::repeat_with(|| rng.sample(Alphanumeric))
            .take(10)
            .map(char::from)
            .collect::<String>();

        // Check if the password meets the criteria
        if password.chars().any(|c| c.is_lowercase())
            && password.chars().any(|c| c.is_uppercase())
            && password.chars().filter(|c| c.is_numeric()).count() >= 3
        {
            break;
        }
    }

    println!("Generated password: {}", password);
}