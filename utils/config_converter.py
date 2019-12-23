def convert_parameters(config):
    '''
    Reads a loaded ConfigParser object and converts matching strings to the
    appropriate data structure.

    Example usage in config.ini:
    * 5 -> 5 (int)
    * "5" -> 5 (string)
    * 5.2 -> 5.2 (float)
    * True -> True (boolean)
    * "True" -> True (string)

    :param config: ConfigParser - config parser object that has read a file
    :return: dict - dictionary of configurations with proper data structure
    '''
    config_dict = dict(config)

    for key, value in config_dict.items():
        # converts sections to dictionary
        config_dict[key] = dict(value)

    for section in config.sections():
        for field in config[section]:

            param = config[section][field]

            if len(param) > 1:
                # parameter forced to string
                if param[0] == '"' and param[-1] == '"':
                    config_dict[section][field] = param[1:-1]
                    continue
                elif param == 'True':
                    config_dict[section][field] = True
                    continue
                elif param == 'False':
                    config_dict[section][field] = False
                    continue

            try:
                # convert to int if possible
                config_dict[section][field] = int(param)
            except ValueError:
                try:
                    # convert to float if possible
                    config_dict[section][field] = float(param)
                except ValueError:
                    pass

    return config_dict
