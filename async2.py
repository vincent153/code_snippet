import asyncio
from asyncio.subprocess import PIPE
from asyncio import create_subprocess_exec


async def _read_stream(stream, callback):
    while True:
        line = await stream.readline()
        if line:
            callback(line)
        else:
            break


async def run(command):
    process = await create_subprocess_exec(
        *command, stdout=PIPE, stderr=PIPE
    )

    await asyncio.wait(
        [
            _read_stream(
                process.stdout,
                lambda x: print(
                    "STDOUT: {}".format(x.decode("UTF8"))
                ),
            ),
            _read_stream(
                process.stderr,
                lambda x: print(
                    "STDERR: {}".format(x.decode("UTF8"))
                ),
            ),
        ]
    )

    await process.wait()


async def main():
    await run(["./dummyProcess.sh"])


if __name__ == "__main__":
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())