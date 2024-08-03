/*
    Written 26/07/2024 by ct.
    A program that salts and hashes a password.
*/

// Import needed libraries.
import Foundation

// Get random number.
var bytes = [Int8](repeating: 0, count: 10)
let status = SecRandomCopyBytes(kSecRandomDefault, bytes.count, &bytes)

if status == errSecSuccess { // Always test the status.
    print(bytes)
    // Prints something different every time you run.
}

/*
    Start of logic.
*/

// Set a password.
let password = "Thisisreallyg00d!"

// Set the characters to use.
let alphabet = "abcdefghijklmnopqrstuvwxyz" +
                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ" +
                       "1234567890" +
                       "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

// Print it.
print("Password: \(password)")
print("Alphabet: \(alphabet)")