import math
import time
import pygame
import os
import random
from midiutil import MIDIFile

# ------------------------------------------------------------
# Utility Functions
# ------------------------------------------------------------

def generate_euclidean_sequence(pulses, steps, rotation):
    seq = []
    accumulator = 0
    for i in range(steps):
        accumulator += pulses
        if accumulator >= steps:
            seq.append(1)
            accumulator -= steps
        else:
            seq.append(0)

    if rotation > 0:
        seq = seq[rotation:] + seq[:rotation]
    return seq


def create_event(ts, duration, sample):
    return {
        "ts" : ts,
        "duration" : duration,
        "sample" : sample
    }

def validate_int(value):
    try:
        int(value)
        return True
    except ValueError:
        return False


def user_input(min_val, max_val, prompt, default):
    while True:
        print(f"{prompt} (default: {default})")
        val = input("> ")
        if val == "":
            return default
        elif validate_int(val):
            val = int(val)
            if min_val <= val <= max_val:
                return val
        print(f"Invalid input. Please enter a number between {min_val} and {max_val}.")


def choose_sample(samples, default):

    names = list(samples.keys())
    while True:
        print("Select a sample (leave empty for default):")
        for i, name in enumerate(names):
            print(f"[{i}] {name}")
        val = input("> ")
        if val == "":
            return names[default % len(names)]
        if validate_int(val):
            idx = int(val)
            if 0 <= idx < len(names):
                return names[idx]
        print("Invalid choice. Please try again.")


# def seq_to_dict(seq, sample, steps, total_steps, q_note_duration):
#     events = []
#     for i in range(total_steps):
#         if seq[i % steps]:
#             ts = i * q_note_duration
#             events.append(create_event(ts, sample))
#     return events

# funtion to create events
def seq_to_dict(seq, sample, steps, total_steps, q_note_duration):
    events = []
    for i in range(total_steps):
        if seq[i % steps]:
            ts = i * q_note_duration
            # look ahead for duration
            next_i = i + 1
            while next_i < steps and seq[next_i % steps] == 0:
                next_i += 1

            duration = (next_i - i) * q_note_duration
            events.append(create_event(ts, duration, sample))
    return events

def handle_event(event, samples):
    """Play the sound sample for an event."""
    sample = samples.get(event["sample"])
    if sample:
        sample.play()

def retry():
    while True:
        again = input("\nWould you like to play again? (y/n): ")
        if again == "y":
            return True
        elif again == "n":
            return False

def generate_midi(events, bpm, q_note_duration):

    # set the necessary values for MIDI util
    velocity=80
    track = 0
    channel = 9 # corresponds to channel 10 drums
    bpm = 120


    # create the MIDIfile object, to which we can add notes
    mf = MIDIFile(1)
    # set name and tempo
    time_beginning = 0
    mf.addTrackName(track, time_beginning, "Beat Sample Track")
    mf.addTempo(track, time_beginning, bpm)

    # variables necessary for transforming events to midi output
    q_note_duration = 60 / bpm
    instr_midi_pitch = {
        "kick": 35,
        "snare": 38,
        "hi-hat": 40
    }


    for event in events:
        # transform time (sec) to (qnote)
        qnote_time = event["ts"] / q_note_duration
        instr_name = event["sample"]
        mf.addNote(track, channel, instr_midi_pitch[instr_name], qnote_time,
            event['duration'], velocity)

    with open("Euclidean_MIDI.midi",'wb') as outf:
        mf.writeFile(outf)



# -----------------------------------------------------------------
# Main Sequence Function
# -----------------------------------------------------------------

def run_sequence(samples):
    bpm = user_input(30, 300, "\nEnter BPM", 120)
    q_note_duration = 60.0 / bpm
    steps = user_input(2, 32, "Enter number of steps per bar", 7)
    bars = user_input(1, 16, "Enter number of bars", 8)
    total_steps = bars * steps
    layers = user_input(1, 10, "Enter number of layers", 3)

    event_list = []

    for i in range(layers):
        print(f"\n--- Layer {i+1} ---")
        default_pulses = random.randint(0, steps)
        pulses = user_input(0, steps, "Enter number of pulses", default_pulses)
        rotation = user_input(0, steps, "Enter rotation amount", 0)
        sample = choose_sample(samples, default=i)
        seq = generate_euclidean_sequence(pulses, steps, rotation)
        event_list += seq_to_dict(seq, sample, steps, total_steps, q_note_duration)

    event_list.sort(key=lambda e: e["ts"])
    print("\nStarting sequence...\n")

    time_zero = time.time()

    if not event_list:
        print("No events to play.")
        return

    events = event_list
    
    next_event = event_list.pop(0)

    try:
        while True:
            now = time.time() - time_zero

            if now >= next_event["ts"]:
                handle_event(next_event, samples)
                if event_list:
                    next_event = event_list.pop(0)
                else:
                    time.sleep(q_note_duration)
                    break
            time.sleep(0.001)

    except KeyboardInterrupt:
        print("\nStopped manually by user (Ctrl+C).")
  
    print("\nSequence finished!\n")
    
    #Save midi
    while True:
        save = input("\nSave Midi? (y/n): ")
        if save == "y":
            generate_midi(events, bpm, q_note_duration)
            break
        elif save == "n":
            break

# ------------------------------------------------------------
# Initialization
# ------------------------------------------------------------


pygame.init()
pygame.mixer.init(frequency=44100, size=-16, channels=2, buffer=512)

samples = {
    "kick": "samples/kick-02.wav",
    "snare": "samples/snare-05.wav",
    "hi-hat": "samples/hihat06.wav",
    "clap": "samples/clap-filtered.wav"
}

# Check samples
loaded_samples = {}
for name, path in samples.items():
    if os.path.exists(path):
        loaded_samples[name] = pygame.mixer.Sound(path)
    else:
        print(f"Missing sample: {path}")

print("Euclidean Sequencer Ready")

while True:
    run_sequence(loaded_samples)
    if not retry():
        break


    
pygame.quit()

