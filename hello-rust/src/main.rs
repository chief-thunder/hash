/*
    Hashing and salting passwords in Rust 🦀.
    Written by ct 22/04/2025, with the help of CoPilot.
*/

use rand::{distributions::Alphanumeric, Rng};
use sha2::{Digest, Sha256};
use md5;
use argon2::{password_hash::{PasswordHasher, SaltString}, Argon2};
use std::iter;

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

// Function to hash a string using MD5 or SHA256
fn hash_it(input: &str, hash_name: &str) -> String {
    match hash_name.to_lowercase().as_str() {
        "md5" => {
            let result = md5::compute(input.as_bytes());
            format!("{:x}", result)
        }
        "sha256" => format!("{:x}", Sha256::digest(input.as_bytes())),
        _ => format!("Error: Unsupported hash type '{}'", hash_name),
    }
}

// Function to hash a salted string using MD5 or SHA256
fn hash_and_salt(salt: &str, input: &str, hash_name: &str) -> String {
    let salted_input = format!("{}{}", salt, input);
    hash_it(&salted_input, hash_name)
}

fn main() {
    // Set password
    let password = "Thisisreallyg00d!";

    // Generate salt
    let salt = get_salt();

    // Print results
    println!("Password: {}", password);
    println!("Salt: {}", salt);
    println!("Salted password: {}{}", salt, password);
    println!("MD5 Hash (unsalted): {}", hash_it(password, "md5"));
    println!("MD5 Hash (salted): {}", hash_and_salt(&salt, password, "md5"));
    println!("SHA256 Hash (unsalted): {}", hash_it(password, "sha256"));
    println!(
        "SHA256 Hash (salted): {}",
        hash_and_salt(&salt, password, "sha256")
    );

    // Argon2id hashing
    let argon2 = Argon2::default();
    let salt_string = match SaltString::b64_encode(salt.as_bytes()) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("Error encoding salt: {}", e);
            return;
        }
    };

    let argon2_hash = match argon2.hash_password(password.as_bytes(), &salt_string) {
        Ok(hash) => hash.to_string(),
        Err(e) => {
            eprintln!("Error hashing with Argon2: {}", e);
            return;
        }
    };
    println!("Argon2id Hash (salted): {}", argon2_hash);
}