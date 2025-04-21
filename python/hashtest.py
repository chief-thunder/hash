###
# Hashing and salting passwords in Python. 🐍
# Written 30/06/2024 by ct.
###

# Import libraries.
import string, secrets, hashlib, os
from argon2 import PasswordHasher, Type

ph = PasswordHasher(
    time_cost=4,
    memory_cost=65536,
    parallelism=2,
    hash_len=32,
    salt_len=16,
    type=Type.ID
)

# Clear the screen.
os.system('clear')

# Create salt function.
def getsalt(mystr):
    while True:
        # Generate a random salt.
        # The salt must be 10 characters long, contain at least one lowercase and uppercase letter and a number.
        salt = ''.join(secrets.choice(mystr) for i in range(10))
        if (any(c.islower() for c in salt)
                and any(c.isupper() for c in salt)
                and sum(c.isdigit() for c in salt) >= 3):
            break
    return salt

# Create hash function.
def hashit(hstr: str,hname: str):
    # Hash it.
    if hname.lower() == "md5":
        hash = hashlib.md5(hstr.encode('utf-8')).hexdigest()
    elif hname.lower() == 'sha256':
        hash = hashlib.sha256(hstr.encode('utf-8')).hexdigest()
    # Return hash.
    return hash

def hashnsalt(sstr: str,hstr: str,hname: str):
    # Salt the password.
    saltpassword = sstr + hstr

    # Hash with salt.
    if hname.lower() == "md5":
        hash = hashlib.md5(saltpassword.encode('utf-8')).hexdigest()
    elif hname.lower() == 'sha256':
        hash = hashlib.sha256(saltpassword.encode('utf-8')).hexdigest()
    # Return hash.
    return hash

### Start of logic

# Set password.
password = "Thisisreallyg00d!"

# Set dynamics of the salt.
alphabet = string.ascii_letters + string.digits + string.punctuation

# Get randoms salt.
salt = getsalt(alphabet)

# Print it.
print("Password: ", password)
print("Salt: ", salt)
print("Salted password: ", salt + password)
print("MD5 Hash (unsalted): ", hashit(password, "md5"))
print("MD5 Hash (salted): ", hashnsalt(salt, password, "md5"))
print("SHA256 Hash (unsalted): ", hashit(password, "sha256"))
print("SHA256 Hash (salted): ", hashnsalt(salt, password, "sha256"))
print("Argon2id Hash (salted): ", ph.hash(password))