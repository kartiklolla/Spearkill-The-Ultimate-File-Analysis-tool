import os
from datetime import datetime
import getpass

LOG_FILE = "Naughtylist_spearkill.log"
HEADER = "WHO GOT CAUGHT BEING NAUGHTY!!!!\n"

def ensure_header():
    # Check if the log file exists
    if not os.path.exists(LOG_FILE):
        # Create the file and add the header
        with open(LOG_FILE, "w") as file:
            file.write(HEADER)
    else:
        # Check if the header exists, and add it if missing
        with open(LOG_FILE, "r") as file:
            content = file.readlines()
        if not content or content[0].strip() != HEADER.strip():
            with open(LOG_FILE, "w") as file:
                file.write(HEADER)
                file.writelines(content)

def log_usage():
    # Ensure the header is present
    ensure_header()
    
    # Get the username of the current user
    username = getpass.getuser()
    
    # Get the current time
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    
    # Append the log entry
    with open(LOG_FILE, "a") as file:
        file.write(f"User: {username}, Time: {current_time}\n")
    print(f"User activity logged: {username} at {current_time}")

# Main execution
if __name__ == "__main__":
    log_usage()

