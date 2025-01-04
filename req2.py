import logging
from datetime import datetime
import getpass
import os

LOG_DIR = os.path.expanduser("~/spearkill_logs")
LOG_FILE = os.path.join(LOG_DIR, "spearkill_error.log")

def setup_logging():
    os.makedirs(LOG_DIR, exist_ok=True)
    logging.basicConfig(
        filename=LOG_FILE,
        level=logging.INFO,
        format="%(message)s",
    )
    if os.stat(LOG_FILE).st_size == 0:  # Add header only if file is empty
        logging.info("WHO GOT CAUGHT BEING NAUGHTY!!!!\n")

def log_usage():
    setup_logging()
    username = getpass.getuser()
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    logging.info(f"User: {username}, Time: {current_time}")

if __name__ == "__main__":
    log_usage()

