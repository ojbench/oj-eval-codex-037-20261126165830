"""Compare the executable against Python's list on reproducible inputs."""
import random
import subprocess
import sys

executable = sys.argv[1] if len(sys.argv) > 1 else "./code"
for seed in range(100):
    rng = random.Random(seed)
    values = []
    operations = ["0", "4", "2 0", "2 -1"]
    expected = ["0", "-1", "-1", "-1"]
    for _ in range(2000):
        op = rng.randrange(5)
        if op == 3 and not values:
            op = 1
        if op == 0:
            operations.append("0")
            expected.append(str(len(values)))
        elif op == 1:
            p = rng.randrange(len(values) + 1)
            x = rng.randint(-2147483648, 2147483647)
            operations.append(f"1 {p} {x}")
            values.insert(p, x)
        elif op == 2:
            p = rng.randint(-2, len(values) + 2)
            operations.append(f"2 {p}")
            expected.append(str(values[p] if 0 <= p < len(values) else -1))
        elif op == 3:
            p = rng.randrange(len(values))
            operations.append(f"3 {p}")
            values.pop(p)
        else:
            operations.append("4")
            expected.append(" ".join(map(str, values)) if values else "-1")
    data = str(len(operations)) + "\n" + "\n".join(operations) + "\n"
    result = subprocess.run([executable], input=data, text=True,
                            capture_output=True, check=True)
    assert result.stdout.splitlines() == expected, f"Mismatch for seed {seed}"
print("Passed 100 randomized cases (200,400 operations).")
