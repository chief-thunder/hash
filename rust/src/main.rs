/*
    Hashing and salting passwords in Rust 🦀.
    Written by ct 22/04/2025, with the help of CoPilot.
*/

use rand::{distributions::Alphanumeric, Rng};
use sha2::{Digest, Sha256};
use md5;
use argon2::{password_hash::{PasswordHasher, SaltString}, Argon2};
use std::iter;
use std::io;

// Function to generate a random salt
fn get_salt() -> String {
    loop {
        let salt: String = iter::repeat_with(|| rand::thread_rng().sample(Alphanumeric))
            .take(10)
            .map(|c| c as char)
            .collect();

        if salt.chars().any(|c| c.is_lowercase())
            && salt.chars().any(|c| c.is_uppercase())
            && salt.chars().filter(|c| c.is_numeric()).count() >= 3
        {
            return salt;
        }
    }
}

// Function to hash a string using MD5, SHA256, or Argon2id
fn hash_it(input: &str, hash_name: &str, salt: Option<&str>) -> String {
    match hash_name.to_lowercase().as_str() {
        "md5" => {
            let result = md5::compute(input.as_bytes());
            format!("{:x}", result)
        }
        "sha256" => format!("{:x}", Sha256::digest(input.as_bytes())),
        "argon2id" => {
            match salt {
                Some(salt_str) => {
                    let argon2 = Argon2::default();
                    let salt_string = match SaltString::b64_encode(salt_str.as_bytes()) {
                        Ok(s) => s,
                        Err(e) => return format!("Error encoding salt: {}", e),
                    };
                    match argon2.hash_password(input.as_bytes(), &salt_string) {
                        Ok(hash) => hash.to_string(),
                        Err(e) => format!("Error hashing with Argon2: {}", e),
                    }
                }
                None => "Error: Argon2id requires a salt".to_string(),
            }
        }
        _ => format!("Error: Unsupported hash type '{}'", hash_name),
    }
}

// Function to hash a salted string using MD5, SHA256, or Argon2id
fn hash_and_salt(salt: &str, input: &str, hash_name: &str) -> String {
    match hash_name.to_lowercase().as_str() {
        "argon2id" => hash_it(input, hash_name, Some(salt)),
        _ => {
            let salted_input = format!("{}{}", salt, input);
            hash_it(&salted_input, hash_name, None)
        }
    }
}

fn main() {
    // Get password from user
    print!("Enter password: ");
    io::Write::flush(&mut io::stdout()).expect("Failed to flush stdout");
    
    let stdin = io::stdin();
    let mut password = String::new();
    stdin.read_line(&mut password).expect("Failed to read line");
    let password = password.trim().to_string();

    // Generate salt
    let salt = get_salt();

    // Print results
    println!("Password: {}", password);
    println!("Salt: {}", salt);
    println!("Salted password: {}{}", salt, password);
    println!("MD5 Hash (unsalted): {}", hash_it(&password, "md5", None));
    println!("MD5 Hash (salted): {}", hash_and_salt(&salt, &password, "md5"));
    println!("SHA256 Hash (unsalted): {}", hash_it(&password, "sha256", None));
    println!("SHA256 Hash (salted): {}", hash_and_salt(&salt, &password, "sha256"));
    println!("Argon2id Hash (salted): {}", hash_and_salt(&salt, &password, "argon2id"));
}