from src.pyregister import *

if __name__ == "__main__":
    batch = RegisterBatchDLL()

    batch.write("EBX", 15)
    batch.read("EBX")

    batch.execute_to_global()

    batch.write("RBX", EBX + 7)
    batch.read("RBX")

    batch.execute_to_global()

    print(RBX)