import os
import numpy as np

size = [64 * 8000]

a = np.random.rand(size[0]).astype(np.float32) * 10
b = np.random.rand(size[0]).astype(np.float32) * 10
c = np.random.rand(size[0]).astype(np.float32) * 10
c2 = c + a * b

size = np.array(size, dtype=np.uint32)

size.tofile(os.path.join(os.path.dirname(__file__), "size.bin"))
a.tofile(os.path.join(os.path.dirname(__file__), "a.bin"))
b.tofile(os.path.join(os.path.dirname(__file__), "b.bin"))
c.tofile(os.path.join(os.path.dirname(__file__), "c.bin"))
c2.tofile(os.path.join(os.path.dirname(__file__), "c2.bin"))
