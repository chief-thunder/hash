###
# Hashing and salting passwords in Python. 🐍
# Written by ct 30/06/2024.
###

import string, secrets, hashlib, os

# Clear the screen.
os.system('clear')

# Create salt function.
def getsalt(mystr):
    while True:
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
password = "Thisisreallyg00d"

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