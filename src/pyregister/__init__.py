import os
import ctypes
import sys
import platform

class RegisterBatch:
    def __init__(self):
        LibPath = None

        if platform.system() == 'Windows':
<<<<<<< HEAD:src/pyregister.py
                LibPath = r'./Pyregister/bin/pyregister.dll'
        else:
            LibPath = r'./Pyregister/bin/libpyregister.so'
=======
                LibPath = r'./bin/pyregister.dll'
        else:
            LibPath = r'./bin/libpyregister.so'
>>>>>>> 680031c (Pyregister Library version 1.1):src/pyregister/__init__.py
        
        if not os.path.exists(LibPath):
            raise FileNotFoundError(f"DLL not founded: \'{LibPath}\'")
        
        self._dll = ctypes.CDLL(LibPath)
        self._dll.read_register.argtypes = [ctypes.c_char_p]
        self._dll.read_register.restype  = None
        self._dll.write_register.argtypes = [ctypes.c_char_p, ctypes.c_uint32]
        self._dll.write_register.restype  = None
        self._dll.execute.argtypes = []
        self._dll.execute.restype  = ctypes.c_char_p

    def write(self, reg: str, val: int):
        self._dll.write_register(reg.encode('ascii'), ctypes.c_uint32(val))

    def read(self, reg: str):
        self._dll.read_register(reg.encode('ascii'))

    def execute(self) -> dict:
        raw = self._dll.execute()
        if not raw:
            return {}
        text = raw.decode('ascii')
        parts = [p for p in text.split("[,013.,45gsd]") if p]
        res = {}
        for part in parts:
            r, v = part.split("[:567:]")
            res[r] = int(v)
        return res
    
    def execute_to_global(self):
        data = self.execute()
        main_mod = sys.modules['__main__']
        main_mod.__dict__.update(data)
